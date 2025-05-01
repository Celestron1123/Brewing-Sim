/**
 * Main brewing class for Brazil.
 *
 * @authors Steven Luo, Julia Maia, Elijah Potter
 * @date 04/24/2025
 *
 * Checked by Julia Maia
 */


#include "brazil.h"
#include "ui_brazil.h"
#include "mainwindow.h"

Brazil::Brazil(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Brazil)
    , world(b2Vec2(0.0f, -10.0f))
    , timer()
{
    ui->setupUi(this);

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if(mainWindow) {
        connect(this,
                &Brazil::goToPress,
                mainWindow,
                &MainWindow::startBrazilPress);
    }

    background = QPixmap(":/Resources/cachacaBackground.png");
    table = QPixmap(":/Resources/table.png");
    sugarcaneBowl = QPixmap(":/Resources/bowl.png");
    cauldron = QPixmap(":/Resources/cauldron.png");
    cauldronFront = QPixmap(":/Resources/cauldronFront.png");
    juiceImage = QPixmap(":/Resources/sugarcaneJuice.png");

    // Dimensions for play-box
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
        leftPot.SetAsBox(0.5f, 13.0f, b2Vec2(-9.0f, 3.0f ), 0);
        wallBody->CreateFixture(&leftPot, 0.0f);
    }

    // Right pot
    {
        b2PolygonShape rightPot;
        rightPot.SetAsBox(0.5f, 13.0f, b2Vec2(9.0f, 3.0f ), 0);
        wallBody->CreateFixture(&rightPot, 0.0f);
    }

    // Bottom bot
    {
        b2PolygonShape bottomPot;
        bottomPot.SetAsBox(9.0f, 0.5f, b2Vec2(0.0f, 3.0f), 0);
        wallBody->CreateFixture(&bottomPot, 0.0f);
    }

    // Left Yeast Bowl
    {
        b2PolygonShape leftYBowl;
        leftYBowl.SetAsBox(4.0f, 0.5f, b2Vec2(19.0f, 0.0f), -60.0f);
        wallBody->CreateFixture(&leftYBowl, 0.0f);
    }

    // Right Yeast Bowl
    {
        b2PolygonShape rightYBowl;
        rightYBowl.SetAsBox(4.0f, 0.5f, b2Vec2(25.0f, 0.0f), 60.0f);
        wallBody->CreateFixture(&rightYBowl, 0.0f);
    }

    // Lets us use wallBody's properties in other methods
    groundBody = wallBody;

    // Define the body definition for the juice
    b2BodyDef sugarcaneJuiceDef;
    sugarcaneJuiceDef.type = b2_dynamicBody;
    sugarcaneJuiceDef.position.Set(-27.0f, -20.0f);

    // Create the body in the world
    sugarcaneJuice = world.CreateBody(&sugarcaneJuiceDef);

    // Define the box shape (half-width, half-height)
    b2PolygonShape boxShape;
    boxShape.SetAsBox(2.5f, 5.0f);  // Creates a 5x10 box

    // Set up fixture properties
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.0f;

    // Attach the shape to the body
    sugarcaneJuice->CreateFixture(&fixtureDef);

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
    connect(&timer, &QTimer::timeout, this, &Brazil::updateTime);
}
Brazil::~Brazil()
{
    delete ui;
}

void Brazil::startPhysics()
{
    timer.start();
}

void Brazil::updateTime()
{
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    world.Step(timeStep, velocityIterations, positionIterations);
    // trigger repaint
    update();
}

// Helper to convert Qt widget coordinates to Box2D world coordinates
b2Vec2 Brazil::screenToWorld(const QPoint &point) {
    // Scaling factor - 10 chosen for simplicity
    const float scale = 10.0f;
    float worldX = (point.x() - width()/2) / scale;
    float worldY = (height()/2 - point.y()) / scale;
    return b2Vec2(worldX, worldY);
}

void Brazil::mousePressEvent(QMouseEvent *event) {
    b2Vec2 clickPoint = screenToWorld(event->pos());

    // Check if the mouse click is on an item's fixture

    if (sugarcaneJuice && sugarcaneJuice->GetFixtureList()->TestPoint(clickPoint)) {
        b2MouseJointDef mouseDef;
        mouseDef.bodyA = groundBody;
        mouseDef.bodyB = sugarcaneJuice;
        mouseDef.target = clickPoint;
        mouseDef.maxForce = 1000.0f * sugarcaneJuice->GetMass();
        mouseDef.collideConnected = true;
        mouseJoint = (b2MouseJoint*) world.CreateJoint(&mouseDef);
    }

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

void Brazil::mouseMoveEvent(QMouseEvent *event) {
    if (mouseJoint) {
        b2Vec2 worldPoint = screenToWorld(event->pos());
        mouseJoint->SetTarget(worldPoint);
    }
}

void Brazil::mouseReleaseEvent(QMouseEvent *event) {
    Q_UNUSED(event);
    if (mouseJoint) {
        world.DestroyJoint(mouseJoint);
        mouseJoint = nullptr;
    }
}

void Brazil::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen(Qt::black);
    pen.setWidth(4);
    painter.setPen(pen);

    // Draw background
    painter.drawPixmap(0, 0, width(), height(), background);

    // Draw workbench
    painter.drawPixmap(0, 275, width(), height(), table);

    // Draw bowl
    painter.drawPixmap(690, 490, width()/6, height()/6, sugarcaneBowl);

    // Draw pot
    painter.drawPixmap(420, 320, width()/4, width()/4, cauldron);

    // Same scaling factor in screenToWorld
    const float scale = 10.0f;

    // Draw sugar cane juice only if it exists
    if (sugarcaneJuice) {
        b2Vec2 pos = sugarcaneJuice->GetPosition();
        float angle = sugarcaneJuice->GetAngle();
        float boxWidth = 10.0f;
        float boxHeight = 10.0f;
        float screenX = width() / 2 + pos.x * scale;
        float screenY = height() / 2 - pos.y * scale;
        float scaledWidth = boxWidth * scale;
        float scaledHeight = boxHeight * scale;
        painter.save();
        painter.translate(screenX, screenY);
        painter.rotate(-angle * 180.0f / M_PI);
        painter.drawPixmap(-scaledWidth / 2, -scaledHeight / 2, scaledWidth,
                           scaledHeight, juiceImage);
        painter.restore();
    }

    for (auto cell : yeast)
    {
        b2Vec2 pos = cell->GetPosition();
        float radius = 0.5f;  // same as ball’s defined radius

        float screenX = width() / 2 + pos.x * scale;
        float screenY = height() / 2 - pos.y * scale;

        painter.setBrush(QColorConstants::Svg::orange);
        painter.drawEllipse(QPointF(screenX, screenY), radius * scale, radius * scale);
    }

    // Draw front of pot
    painter.drawPixmap(420, 320, width()/4, width()/4, cauldronFront);
}

void Brazil::on_continueButton_clicked()
{
    timer.stop();
    if (sugarcaneJuice) {
        world.DestroyBody(sugarcaneJuice);
        sugarcaneJuice = nullptr;
    }
    yeast.clear();
    emit goToPress();
}

bool Brazil::ingredientsInPot() const {
    if(!sugarcaneJuice) {
        return false;
    }

    auto isInsidePot = [](const b2Vec2& pos) {
        return pos.x > -12.0f && pos.x < 12.0f && pos.y > -20.0f && pos.y < 7.0f;
    };

    if(!isInsidePot(sugarcaneJuice->GetPosition())) {
        return false;
    }

    for (b2Body* cell : yeast) {
        if (!isInsidePot(cell->GetPosition())) {
            return false;
        }
    }
    return true;
}

void Brazil::on_dragSkip_clicked()
{
    // Move all balls into the pot instantly
    float potY = -5.0f;  // reasonable height inside the pot
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

    if (sugarcaneJuice) {
        // Adjust these values to center the juice better within the pot's logical boundaries
        b2Vec2 juicePos = b2Vec2(0.0f, -2.0f);
        sugarcaneJuice->SetTransform(juicePos, 0);
    }

    update();
}

