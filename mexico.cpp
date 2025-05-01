#include "mexico.h"
#include "ui_mexico.h"
#include "mainwindow.h"

Mexico::Mexico(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Mexico)
    , world(b2Vec2(0.0f, -10.0f))
    , timer()
{
    ui->setupUi(this);

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if(mainWindow) {
        connect(this,
                &Mexico::goToOutro,
                mainWindow,
                &MainWindow::startMexicoOutro);
    }

    background = QPixmap(":/Resources/mexicanbgblur.png");
    table = QPixmap(":/Resources/table.png");
    bucket = QPixmap(":/Resources/mexbucketliquid.png");
    bucketFront = QPixmap(":/Resources/mexbucketfront.png");
    bowl = QPixmap(":/Resources/mexicobowl.png");

    float worldWidth = 90.0f;
    float worldHeight = 50.0f;

    // Create a ground/static body for boundaries
    b2BodyDef wallDef;
    wallDef.position.Set(0.0f, -25.0f);
    b2Body* wallBody = world.CreateBody(&wallDef);

    // Left wall
    {
        b2PolygonShape leftWall;
        leftWall.SetAsBox(0.5f, worldHeight/2, b2Vec2(-worldWidth/2 - 0.5f, worldHeight/2), 0);
        wallBody->CreateFixture(&leftWall, 0.0f);
    }

    // Right wall
    {
        b2PolygonShape rightWall;
        rightWall.SetAsBox(0.5f, worldHeight/2, b2Vec2(worldWidth/2 + 0.5f, worldHeight/2), 0);
        wallBody->CreateFixture(&rightWall, 0.0f);
    }

    // Top wall
    {
        b2PolygonShape topWall;
        topWall.SetAsBox(worldWidth/2, 0.5f, b2Vec2(0, worldHeight + 0.5f), 0);
        wallBody->CreateFixture(&topWall, 0.0f);
    }

    // Bottom wall
    {
        b2PolygonShape bottomWall;
        bottomWall.SetAsBox(worldWidth/2, 0.5f, b2Vec2(0, -0.5f), 0);
        wallBody->CreateFixture(&bottomWall, 0.0f);
    }

    // Left pot
    {
        b2PolygonShape leftPot;
        leftPot.SetAsBox(0.5f, 13.0f, b2Vec2(-12.0f, 3.0f ), 0);
        wallBody->CreateFixture(&leftPot, 0.0f);
    }

    // Right pot
    {
        b2PolygonShape rightPot;
        rightPot.SetAsBox(0.5f, 13.0f, b2Vec2(12.0f, 3.0f ), 0);
        wallBody->CreateFixture(&rightPot, 0.0f);
    }

    // Bottom bot
    {
        b2PolygonShape bottomPot;
        bottomPot.SetAsBox(12.0f, 0.5f, b2Vec2(0.0f, 3.0f), 0);
        wallBody->CreateFixture(&bottomPot, 0.0f);
    }

    // Left Yeast Bowl
    {
        b2PolygonShape leftYBowl;
        leftYBowl.SetAsBox(4.0f, 0.5f, b2Vec2(19.0f, 1.3f), -60.0f);
        wallBody->CreateFixture(&leftYBowl, 0.0f);
    }

    // Right Yeast Bowl
    {
        b2PolygonShape rightYBowl;
        rightYBowl.SetAsBox(4.0f, 0.5f, b2Vec2(25.0f, 1.3f), 60.0f);
        wallBody->CreateFixture(&rightYBowl, 0.0f);
    }

    groundBody = wallBody;

    // Create the yeast dynamic body
    b2BodyDef yeastDef;
    yeastDef.type = b2_dynamicBody;
    // Create as many balls as iteraions
    float xPosYeast = 19.0f;
    float yPosYeast = -15.0f;
    for (int i = 0.0f; i < 8; i++)
    {
        yeastDef.position.Set(xPosYeast, yPosYeast);
        b2Body* cell = world.CreateBody(&yeastDef);

        // Define the circle shape representing the ball
        b2CircleShape circleShape;
        circleShape.m_radius = 0.5f;

        // Set up fixture properties: density, friction, and restitution
        b2FixtureDef ballFixtureDef;
        ballFixtureDef.shape = &circleShape;
        ballFixtureDef.density = 1.0f;
        ballFixtureDef.friction = 0.3f;
        ballFixtureDef.restitution = 0.3f;

        cell->CreateFixture(&ballFixtureDef);

        yeast.push_back(cell);

        xPosYeast += 3.0f;
        if (xPosYeast > 25.0f)
        {
            xPosYeast = 19.0f;
            yPosYeast += 3.0f;
        }
    }


    timer.setInterval(10);
    connect(&timer, &QTimer::timeout, this, &Mexico::updateTime);
    connect(ui->dragSkip, &QPushButton::clicked, this, &Mexico::onAutoMixclicked);
    connect(ui->continuebtn, &QPushButton::clicked, this, &Mexico::onContinueClicked);
}

Mexico::~Mexico()
{
    delete ui;
}

void Mexico::startPhysics()
{
    timer.start();
}

void Mexico::updateTime()
{
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    world.Step(timeStep, velocityIterations, positionIterations);
    // trigger repaint
    update();
}

b2Vec2 Mexico::screenToWorld(const QPoint &point) {
    // Scaling factor - 10 chosen for simplicity
    const float scale = 10.0f;
    float worldX = (point.x() - width()/2) / scale;
    float worldY = (height()/2 - point.y()) / scale;
    return b2Vec2(worldX, worldY);
}

void Mexico::mousePressEvent(QMouseEvent *event) {
    b2Vec2 clickPoint = screenToWorld(event->pos());

    for (auto cell : yeast)
    {
        if (cell->GetFixtureList()->TestPoint(clickPoint)) {
            // Define and create a mouse joint
            b2MouseJointDef mouseDef;
            mouseDef.bodyA = groundBody;
            mouseDef.bodyB = cell;
            mouseDef.target = clickPoint;
            mouseDef.maxForce = 1000.0f * cell->GetMass();
            mouseDef.collideConnected = true;
            mouseJoint = (b2MouseJoint*) world.CreateJoint(&mouseDef);
        }
    }
}

void Mexico::mouseMoveEvent(QMouseEvent *event) {
    if (mouseJoint) {
        b2Vec2 worldPoint = screenToWorld(event->pos());
        mouseJoint->SetTarget(worldPoint);
    }
}

void Mexico::mouseReleaseEvent(QMouseEvent *event) {
    Q_UNUSED(event);
    if (mouseJoint) {
        world.DestroyJoint(mouseJoint);
        mouseJoint = nullptr;
    }
}

void Mexico::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen(Qt::black);
    pen.setWidth(4);
    painter.setPen(pen);

    // Draw background
    painter.drawPixmap(0, 0, width(), height(), background);

    //Draw workbench
    painter.drawPixmap(0, 275, width(), height(), table);

    // // Draw bowl
    painter.drawPixmap(690, 490, width()/6, height()/6, bowl);

    // Draw bucket
    painter.drawPixmap(420, 320, width()/4, width()/4, bucket);

    // Same scaling factor in screenToWorld
    const float scale = 10.0f;

    for (auto cell : yeast)
    {
        b2Vec2 pos = cell->GetPosition();
        float radius = 0.5f;  // same as ball’s defined radius

        float screenX = width() / 2 + pos.x * scale;
        float screenY = height() / 2 - pos.y * scale;

        painter.setBrush(QColorConstants::Svg::orange);
        painter.drawEllipse(QPointF(screenX, screenY), radius * scale, radius * scale);
    }

    if (ingredientsInPot())
    {
        ui->continuebtn->setDisabled(false);
        ui->dragSkip->setDisabled(true);
        yeast.clear();
        bucket = QPixmap(":/Resources/mexbucketferment.png");
        bucketFront = QPixmap(":/Resources/mexbucketfront.png");
    }
    else
    {
        ui->dragSkip->setDisabled(false);
        ui->continuebtn->setDisabled(true);
    }

    // // Draw front of pot
    painter.drawPixmap(420, 320, width()/4, width()/4, bucketFront);
}

bool Mexico::ingredientsInPot() const {
    auto isInsidePot = [](const b2Body* body) {
        b2Vec2 pos = body->GetPosition();
        return pos.x > -12.0f && pos.x < 12.0f && pos.y < -15.0f;
    };

    for (b2Body* cell : yeast)
        if (!isInsidePot(cell)) return false;

    return true;
}

void Mexico::onAutoMixclicked()
{
    // Move all balls into the bucket instantly
    float potY = 10.0f;
    float potXStart = -4.0f;
    float potXEnd = 4.0f;
    float step = (potXEnd - potXStart) / 6.0f;
    float yStep = 2.5f;

    auto placeBodies = [&](std::vector<b2Body*>& list) {
        float x = potXStart;
        float y = potY;
        for (b2Body* body : list) {
            body->SetTransform(b2Vec2(x, y), 0);
            x += step;
            if (x > potXEnd) {
                x = potXStart;
                y += yStep;
            }
        }
    };

    placeBodies(yeast);

    update();
}

void Mexico::onContinueClicked(){
    timer.stop();
    emit goToOutro();
}
