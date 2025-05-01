#include "japan.h"
#include "ui_japan.h"
#include "mainwindow.h"

Japan::Japan(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Japan)
    , world(b2Vec2(0.0f, -10.0f))
    , timer()
{
    ui->setupUi(this);

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if(mainWindow) {
        connect(this,
                &Japan::goToPress,
                mainWindow,
                &MainWindow::startJapanPress);
    }

    background = QPixmap(":/Resources/sakebackground.png");
    table = QPixmap(":/Resources/table.png");
    kojiBowl = QPixmap(":/Resources/bowl.png");
    cauldron = QPixmap(":/Resources/cauldron.png");
    cauldronFront = QPixmap(":/Resources/cauldronFront.png");

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

    // Left Rice Bowl
    {
        b2PolygonShape leftRBowl;
        leftRBowl.SetAsBox(4.0f, 0.5f, b2Vec2(-19.0f, 0.0f), 60.0f);
        wallBody->CreateFixture(&leftRBowl, 0.0f);
    }

    // Right Rice Bowl
    {
        b2PolygonShape rightRBowl;
        rightRBowl.SetAsBox(4.0f, 0.5f, b2Vec2(-25.0f, 0.0f), -60.0f);
        wallBody->CreateFixture(&rightRBowl, 0.0f);
    }

    // Left Koji Bowl
    {
        b2PolygonShape leftKBowl;
        leftKBowl.SetAsBox(4.0f, 0.5f, b2Vec2(-34.0f, 0.0f), 60.0f);
        wallBody->CreateFixture(&leftKBowl, 0.0f);
    }

    // Right Koji Bowl
    {
        b2PolygonShape rightKBowl;
        rightKBowl.SetAsBox(4.0f, 0.5f, b2Vec2(-40.0f, 0.0f), -60.0f);
        wallBody->CreateFixture(&rightKBowl, 0.0f);
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

    // Create the rice dynamic body
    b2BodyDef riceDef;
    riceDef.type = b2_dynamicBody;
    // Create as many balls as iteraions
    float xPosRice = -25.0f;
    float yPosRice = -15.0f;
    for (int i = 0.0f; i < 6; i++)
    {
        riceDef.position.Set(xPosRice, yPosRice);
        b2Body* grain = world.CreateBody(&riceDef);

        // Define the circle shape representing the ball
        b2CircleShape circleShape;
        circleShape.m_radius = 1.0f;

        // Set up fixture properties: density, friction, and restitution
        b2FixtureDef ballFixtureDef;
        ballFixtureDef.shape = &circleShape;
        ballFixtureDef.density = 1.0f;
        ballFixtureDef.friction = 0.3f;
        ballFixtureDef.restitution = 0.3f;

        grain->CreateFixture(&ballFixtureDef);

        rice.push_back(grain);

        xPosRice += 3.0f;
        if (xPosRice > -19.0f)
        {
            xPosRice = -25.0f;
            yPosRice += 3.0f;
        }
    }

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

    // Create the koji dynamic body
    b2BodyDef kojiDef;
    kojiDef.type = b2_dynamicBody;
    // Create as many balls as iteraions
    float xPosKoji = -40.0f;
    float yPosKoji = -15.0f;
    for (int i = 0.0f; i < 3; i++)
    {
        kojiDef.position.Set(xPosKoji, yPosKoji);
        b2Body* grain = world.CreateBody(&kojiDef);

        // Define the circle shape representing the ball
        b2CircleShape circleShape;
        circleShape.m_radius = 1.5f;

        // Set up fixture properties: density, friction, and restitution
        b2FixtureDef ballFixtureDef;
        ballFixtureDef.shape = &circleShape;
        ballFixtureDef.density = 1.0f;
        ballFixtureDef.friction = 0.3f;
        ballFixtureDef.restitution = 0.0f;

        grain->CreateFixture(&ballFixtureDef);

        koji.push_back(grain);

        xPosKoji += 6.0f;
        if (xPosKoji > -34.0f)
        {
            xPosKoji = -40.0f;
            yPosKoji -= 4.0f;
        }
    }

    timer.setInterval(10);
    connect(&timer, &QTimer::timeout, this, &Japan::updateTime);
}

Japan::~Japan()
{
    delete ui;
}

void Japan::startPhysics()
{
    timer.start();
}

void Japan::updateTime()
{
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    world.Step(timeStep, velocityIterations, positionIterations);
    // trigger repaint
    update();
}

// Helper to convert Qt widget coordinates to Box2D world coordinates
b2Vec2 Japan::screenToWorld(const QPoint &point) {
    // Scaling factor - 10 chosen for simplicity
    const float scale = 10.0f;
    float worldX = (point.x() - width()/2) / scale;
    float worldY = (height()/2 - point.y()) / scale;
    return b2Vec2(worldX, worldY);
}

void Japan::mousePressEvent(QMouseEvent *event) {
    b2Vec2 clickPoint = screenToWorld(event->pos());

    // Check if the mouse click is on a ball's fixture
    for (auto grain : rice)
    {
        if (grain->GetFixtureList()->TestPoint(clickPoint)) {
            // Define and create a mouse joint
            b2MouseJointDef mouseDef;
            mouseDef.bodyA = groundBody;
            mouseDef.bodyB = grain;
            mouseDef.target = clickPoint;
            mouseDef.maxForce = 1000.0f * grain->GetMass();
            mouseDef.collideConnected = true;
            mouseJoint = (b2MouseJoint*) world.CreateJoint(&mouseDef);
        }
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

    for (auto kgrain : koji)
    {
        if (kgrain->GetFixtureList()->TestPoint(clickPoint)) {
            // Define and create a mouse joint
            b2MouseJointDef mouseDef;
            mouseDef.bodyA = groundBody;
            mouseDef.bodyB = kgrain;
            mouseDef.target = clickPoint;
            mouseDef.maxForce = 1000.0f * kgrain->GetMass();
            mouseDef.collideConnected = true;
            mouseJoint = (b2MouseJoint*) world.CreateJoint(&mouseDef);
        }
    }
}

void Japan::mouseMoveEvent(QMouseEvent *event) {
    if (mouseJoint) {
        b2Vec2 worldPoint = screenToWorld(event->pos());
        mouseJoint->SetTarget(worldPoint);
    }
}

void Japan::mouseReleaseEvent(QMouseEvent *event) {
    Q_UNUSED(event);
    if (mouseJoint) {
        world.DestroyJoint(mouseJoint);
        mouseJoint = nullptr;
    }
}

void Japan::paintEvent(QPaintEvent *event) {
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

    // Draw bowls
    painter.drawPixmap(100, 490, width()/6, height()/6, kojiBowl);
    painter.drawPixmap(250, 490, width()/6, height()/6, kojiBowl);
    painter.drawPixmap(690, 490, width()/6, height()/6, kojiBowl);

    // Draw pot
    painter.drawPixmap(420, 320, width()/4, width()/4, cauldron);

    // Same scaling factor in screenToWorld
    const float scale = 10.0f;

    // // Draw the walls from groundBody
    // for (b2Fixture* fixture = groundBody->GetFixtureList(); fixture; fixture = fixture->GetNext()) {
    //     if (fixture->GetShape()->GetType() == b2Shape::e_polygon) {
    //         b2PolygonShape* poly = static_cast<b2PolygonShape*>(fixture->GetShape());
    //         QPolygonF wallPolygon;

    //         // Iterate over each vertex in the polygon
    //         for (int i = 0; i < poly->m_count; ++i) {
    //             // Get the world point for the vertex (transformed by the body's transform)
    //             b2Vec2 worldVertex = groundBody->GetWorldPoint(poly->m_vertices[i]);

    //             // Convert world coordinates to screen coordinates
    //             float screenX = width() / 2 + worldVertex.x * scale;
    //             float screenY = height() / 2 - worldVertex.y * scale;
    //             wallPolygon << QPointF(screenX, screenY);
    //         }
    //         // Set wall color
    //         painter.setBrush(Qt::gray);
    //         painter.drawPolygon(wallPolygon);
    //     }
    // }

    for (auto grain : rice)
    {
        b2Vec2 pos = grain->GetPosition();
        float radius = 1.0f;  // same as ball’s defined radius

        float screenX = width() / 2 + pos.x * scale;
        float screenY = height() / 2 - pos.y * scale;

        painter.setBrush(Qt::white);
        painter.drawEllipse(QPointF(screenX, screenY), radius * scale * 1.5, radius * scale);
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

    for (auto kgrain : koji)
    {
        b2Vec2 pos = kgrain->GetPosition();
        float radius = 1.5f;  // same as ball’s defined radius

        float screenX = width() / 2 + pos.x * scale;
        float screenY = height() / 2 - pos.y * scale;

        painter.setBrush(QColor(255, 253, 208));
        painter.drawEllipse(QPointF(screenX, screenY), radius * scale * 1.5, radius * scale);
    }

    if (ingredientsInPot())
    {
        ui->pushButton->setDisabled(false);
        ui->dragSkip->setDisabled(true);
        rice.clear();
        yeast.clear();
        koji.clear();
        cauldron = QPixmap(":/Resources/cauldronferment.png");
        cauldronFront = QPixmap(":/Resources/cauldronferment.png");
    }
    else
    {
        ui->dragSkip->setDisabled(false);
        ui->pushButton->setDisabled(true);
    }

    // Draw front of pot
    painter.drawPixmap(420, 320, width()/4, width()/4, cauldronFront);
}

void Japan::on_pushButton_clicked()
{
    timer.stop();
    emit goToPress();
}

bool Japan::ingredientsInPot() const {
    auto isInsidePot = [](const b2Body* body) {
        b2Vec2 pos = body->GetPosition();
        return pos.x > -10.0f && pos.x < 10.0f && pos.y < -15.0f;
    };

    for (b2Body* grain : rice)
        if (!isInsidePot(grain)) return false;
    for (b2Body* cell : yeast)
        if (!isInsidePot(cell)) return false;
    for (b2Body* kgrain : koji)
        if (!isInsidePot(kgrain)) return false;

    return true;
}


void Japan::on_dragSkip_clicked()
{
    // Move all balls into the pot instantly
    float potY = 10.0f;  // reasonable height inside the pot
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

    placeBodies(rice);
    placeBodies(koji);
    placeBodies(yeast);

    update();
}

