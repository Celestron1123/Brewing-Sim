/**
 * The implementation of GermanyHop
 *
 * @author Ryan Hamerman
 * @date 04/24/2025
 */

#include "germanyhop.h"
#include "ui_germanyhop.h"
#include "mainwindow.h"

GermanyHop::GermanyHop(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GermanyHop)
    , world(b2Vec2(0.0f, -15.0f))
    , timer()
{
    ui->setupUi(this);

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if(mainWindow) {
        connect(this,
                &GermanyHop::allInPot,
                this,
                [this](){ui->continueButton->setEnabled(true);});

        connect(this,
                &GermanyHop::goToGFerment,
                mainWindow,
                &MainWindow::startGFerment);
    }

    background = QPixmap(":/Resources/hoppingbackground.png");
    table = QPixmap(":/Resources/table.png");
    kojiBowl = QPixmap(":/Resources/bowl.png");
    cauldron = QPixmap(":/Resources/hoppingpot.png");
    cauldronFront = QPixmap(":/Resources/hoppingpotfront.png");
    hop = QPixmap(":/Resources/hopsprite.png");

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
        leftPot.SetAsBox(0.5f, 11.0f, b2Vec2(-8.0f, 3.0f ), 0);
        wallBody->CreateFixture(&leftPot, 0.0f);
    }

    // Right pot
    {
        b2PolygonShape rightPot;
        rightPot.SetAsBox(0.5f, 11.0f, b2Vec2(7.5f, 3.0f ), 0);
        wallBody->CreateFixture(&rightPot, 0.0f);
    }

    // Bottom bot
    {
        b2PolygonShape bottomPot;
        bottomPot.SetAsBox(9.0f, 0.5f, b2Vec2(0.0f, 3.0f), 0);
        wallBody->CreateFixture(&bottomPot, 0.0f);
    }

    // Left Hops Bowl
    {
        b2PolygonShape leftHBowl;
        leftHBowl.SetAsBox(4.0f, 0.5f, b2Vec2(-21.0f, 0.0f), 60.0f);
        wallBody->CreateFixture(&leftHBowl, 0.0f);
    }

    // Right Hops Bowl
    {
        b2PolygonShape rightHBowl;
        rightHBowl.SetAsBox(4.0f, 0.5f, b2Vec2(-27.0f, 0.0f), -60.0f);
        wallBody->CreateFixture(&rightHBowl, 0.0f);
    }

    // Lets us use wallBody's properties in other methods
    groundBody = wallBody;

    // Create the hops dynamic body
    b2BodyDef hopDef;
    hopDef.type = b2_dynamicBody;
    hopDef.angularDamping = 4.0f;
    // Create as many balls as iteraions
    float xPosHop = -23.0f;
    float yPosHop = -15.0f;
    for (int i = 0.0f; i < 8; i++)
    {
        hopDef.position.Set(xPosHop, yPosHop);
        b2Body* grain = world.CreateBody(&hopDef);

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

        hops.push_back(grain);

        xPosHop += 3.0f;
        if (xPosHop > -19.0f)
        {
            xPosHop = -25.0f;
            yPosHop += 3.0f;
        }
    }


    timer.setInterval(10);
    connect(&timer, &QTimer::timeout, this, &GermanyHop::updateTime);
}

GermanyHop::~GermanyHop()
{
    delete ui;
}

void GermanyHop::startPhysics()
{
    timer.start();
}

void GermanyHop::updateTime()
{
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    world.Step(timeStep, velocityIterations, positionIterations);
    // trigger repaint
    update();
}

b2Vec2 GermanyHop::screenToWorld(const QPoint &point) {
    // Scaling factor - 10 chosen for simplicity
    const float scale = 10.0f;
    float worldX = (point.x() - width()/2) / scale;
    float worldY = (height()/2 - point.y()) / scale;
    return b2Vec2(worldX, worldY);
}

void GermanyHop::mousePressEvent(QMouseEvent *event) {
    b2Vec2 clickPoint = screenToWorld(event->pos());

    // Check if the mouse click is on a ball's fixture
    for (auto grain : hops)
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
}

void GermanyHop::mouseMoveEvent(QMouseEvent *event) {
    if (mouseJoint) {
        b2Vec2 worldPoint = screenToWorld(event->pos());
        mouseJoint->SetTarget(worldPoint);
    }
}

void GermanyHop::mouseReleaseEvent(QMouseEvent *event) {
    Q_UNUSED(event);
    if (mouseJoint) {
        world.DestroyJoint(mouseJoint);
        mouseJoint = nullptr;
    }
}

void GermanyHop::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen(Qt::black);
    pen.setWidth(4);
    painter.setPen(pen);

    // Draw background
    painter.drawPixmap(0, 0, width(), height(), background);

    // Draw workbench
    painter.drawPixmap(0, 290, width(), height(), table);

    // Draw bowls
    painter.drawPixmap(230, 490, width()/6, height()/6, kojiBowl);

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

    for (auto grain : hops)
    {
        b2Vec2 pos = grain->GetPosition();
        float radius = 1.0f;  // same as ball’s defined radius
        float angle = grain->GetAngle();

        float screenX = width() / 2 + pos.x * scale;
        float screenY = height() / 2 - pos.y * scale;

        float pixSize = radius * scale * 4.0f;
        int w = int(pixSize), h = int(pixSize);

        painter.save();
        painter.translate(screenX, screenY);
        painter.rotate(angle * 180.0f / float(M_PI));
        painter.drawPixmap(-w/2, -h/2, w, h, hop);
        painter.restore();
    }

    // Draw front of pot
    painter.drawPixmap(420, 320, width()/4, width()/4, cauldronFront);

    if(hopsInPot()) {
        emit allInPot();
    }
}

bool GermanyHop::hopsInPot() const {
    auto isInsidePot = [](const b2Body* body) {
        b2Vec2 pos = body->GetPosition();
        return pos.x > -8.0f && pos.x < 7.5f && pos.y < -10.0f;
    };

    for (b2Body* g : hops)
        if (!isInsidePot(g)) return false;

    return true;
}

void GermanyHop::on_continueButton_clicked()
{
    emit goToGFerment();
}

