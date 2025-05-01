/**
 * The implementation of CaribbeanBoiling
 *
 * @author Steven Luo
 * @date 04/24/2025
 */

#include "caribbeanboiling.h"
#include "Box2D/Dynamics/b2Body.h"
#include "qpainter.h"
#include "ui_caribbeanboiling.h"
#include "mainwindow.h"
#include <QMouseEvent>

CaribbeanBoiling::CaribbeanBoiling(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CaribbeanBoiling)
    , world(b2Vec2(0.0f, -10.0f))
    , timer()
{
    ui->setupUi(this);

    background = QPixmap(":/Resources/rumbackground.png");
    table = QPixmap(":/Resources/table.png");
    pot = QPixmap(":/Resources/caribbeanPot.png");
    potFront = QPixmap(":/Resources/caribbeanPotFront.png");

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

    // Bottom pot
    {
        b2PolygonShape bottomPot;
        bottomPot.SetAsBox(9.0f, 0.5f, b2Vec2(0.0f, 3.0f), 0);
        wallBody->CreateFixture(&bottomPot, 0.0f);
    }

    // Lets us use wallBody's properties in other methods
    groundBody = wallBody;

    b2BodyDef sugarCaneJuiceDef;
    sugarCaneJuiceDef.type = b2_dynamicBody;
    sugarCaneJuiceDef.position.Set(-27.0f, -20.0f);

    sugarCaneJuice = world.CreateBody(&sugarCaneJuiceDef);

    b2PolygonShape boxShape;
    // Creates a 5x10 box
    boxShape.SetAsBox(2.5f, 5.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.0f;

    sugarCaneJuice->CreateFixture(&fixtureDef);

    timer.setInterval(10);
    connect(&timer, &QTimer::timeout, this, &CaribbeanBoiling::updateTime);

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if(mainWindow) {
        connect(this,
                &CaribbeanBoiling::goToFermentation,
                mainWindow,
                &MainWindow::startCaribbeanFermentation);
    }
}

void CaribbeanBoiling::startPhysics()
{
    timer.start();
}

void CaribbeanBoiling::updateTime() {
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    world.Step(timeStep, velocityIterations, positionIterations);

    // Check if juice is in pot and update button state
    if (sugarCaneJuice && isJuiceInPot()) {
        ui->boilButton->setEnabled(true);
    } else {
        ui->boilButton->setEnabled(false);
    }

    update();
}

b2Vec2 CaribbeanBoiling::screenToWorld(const QPoint &point) {
    const float scale = 10.0f;
    float worldX = (point.x() - width()/2) / scale;
    float worldY = (height()/2 - point.y()) / scale;
    return b2Vec2(worldX, worldY);
}

void CaribbeanBoiling::mousePressEvent(QMouseEvent *event) {
    b2Vec2 clickPoint = screenToWorld(event->pos());

    if (sugarCaneJuice && sugarCaneJuice->GetFixtureList()->TestPoint(clickPoint)) {
        b2MouseJointDef mouseDef;
        mouseDef.bodyA = groundBody;
        mouseDef.bodyB = sugarCaneJuice;
        mouseDef.target = clickPoint;
        mouseDef.maxForce = 1000.0f * sugarCaneJuice->GetMass();
        mouseDef.collideConnected = true;
        mouseJoint = (b2MouseJoint*) world.CreateJoint(&mouseDef);
    }

    if (molasses && molasses->GetFixtureList()->TestPoint(clickPoint)) {
        b2MouseJointDef mouseDef;
        mouseDef.bodyA = groundBody;
        mouseDef.bodyB = molasses;
        mouseDef.target = clickPoint;
        mouseDef.maxForce = 1000.0f * molasses->GetMass();
        mouseDef.collideConnected = true;
        mouseJoint = (b2MouseJoint*) world.CreateJoint(&mouseDef);
    }
}

void CaribbeanBoiling::mouseMoveEvent(QMouseEvent *event) {
    if (mouseJoint) {
        b2Vec2 worldPoint = screenToWorld(event->pos());
        mouseJoint->SetTarget(worldPoint);
    }
}

void CaribbeanBoiling::mouseReleaseEvent(QMouseEvent *) {
    if (mouseJoint) {
        world.DestroyJoint(mouseJoint);
        mouseJoint = nullptr;
    }
}

void CaribbeanBoiling::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen(Qt::black);
    pen.setWidth(4);
    painter.setPen(pen);
    const float scale = 10.0f;

    // Draw background
    painter.drawPixmap(0, 0, width(), height(), background);

    // Draw workbench
    painter.drawPixmap(0, 275, width(), height(), table);

    // Draw pot or pot boiling
    painter.drawPixmap(420, 320, width()/4, width()/4, pot);

    // Draw sugar cane juice only if it exists
    if (sugarCaneJuice) {
        b2Vec2 pos = sugarCaneJuice->GetPosition();
        float angle = sugarCaneJuice->GetAngle();
        float boxWidth = 5.0f;
        float boxHeight = 10.0f;
        float screenX = width() / 2 + pos.x * scale;
        float screenY = height() / 2 - pos.y * scale;
        float scaledWidth = boxWidth * scale;
        float scaledHeight = boxHeight * scale;
        painter.save();
        painter.translate(screenX, screenY);
        painter.rotate(-angle * 180.0f / M_PI);
        QPixmap juiceImage(":/Resources/sugarcaneJuiceBox.png");
        painter.drawPixmap(-scaledWidth / 2, -scaledHeight / 2, scaledWidth,
                           scaledHeight, juiceImage);
        painter.restore();
    }

    // Draw molasses if it exists
    if (molasses) {
        b2Vec2 molPos = molasses->GetPosition();
        float molAngle = molasses->GetAngle();
        float molWidth = 6.5f;
        float molHeight = 10.0f;

        float molScreenX = width() / 2 + molPos.x * scale;
        float molScreenY = height() / 2 - molPos.y * scale;

        painter.save();
        painter.translate(molScreenX, molScreenY);
        painter.rotate(-molAngle * 180.0f / M_PI);

        QPixmap molassesBarrelImage(":/Resources/molassesBarrel.png");
        painter.drawPixmap(-molWidth * scale / 2, -molHeight * scale / 2,
                           molWidth * scale, molHeight * scale,
                           molassesBarrelImage);
        painter.restore();
    }

    // Draw front of pot
    painter.drawPixmap(420, 320, width()/4, width()/4, potFront);
}

bool CaribbeanBoiling::isJuiceInPot() const {
    if (!sugarCaneJuice) {
        return false;
    }

    auto isInsidePot = [](const b2Body* body) {
        b2Vec2 pos = body->GetPosition();
        return pos.x > -9.0f && pos.x < 9.0f && pos.y > -20.0f && pos.y < -2.0f;
    };

    return isInsidePot(sugarCaneJuice);
}

void CaribbeanBoiling::createMolasses() {
    b2BodyDef molassesDef;
    molassesDef.type = b2_dynamicBody;

    // Position it to the right of the pot
    molassesDef.position.Set(25.0f, -20.0f);

    b2Body* molassesBody = world.CreateBody(&molassesDef);

    // Define the box shape (half-width, half-height)
    b2PolygonShape boxShape;
    boxShape.SetAsBox(3.25f, 5.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 1.5f;
    fixtureDef.friction = 0.5f;
    fixtureDef.restitution = 0.1f;

    molassesBody->CreateFixture(&fixtureDef);
    molasses = molassesBody;
}

void CaribbeanBoiling::on_boilButton_clicked()
{
    world.DestroyBody(sugarCaneJuice);
    sugarCaneJuice = nullptr;

    pot = QPixmap(":/Resources/caribbeanPotBoiling.png");
    ui->boilButton->setEnabled(false);
    ui->sugarcaneText->hide();

    // Countdown setup
    countdownValue = 3;
    ui->boilCountdownText->setText(QString::number(countdownValue));
    ui->boilCountdownText->show();

    connect(&boilCountdownTimer, &QTimer::timeout, this, [this]() {
        countdownValue--;

        if (countdownValue > 0) {
            ui->boilCountdownText->setText(QString::number(countdownValue));
        } else if (countdownValue == 0) {
            ui->boilCountdownText->setText("Done!");
        } else {
            boilCountdownTimer.stop();
            ui->boilButton->hide();
            ui->boilCountdownText->hide();
            pot = QPixmap(":/Resources/caribbeanPot.png");
            ui->molassesText->setText("Molasses");
            createMolasses();
        }
    });

    boilCountdownTimer.start(1000);
}

void CaribbeanBoiling::on_continueButton_clicked()
{
    emit goToFermentation();
}

CaribbeanBoiling::~CaribbeanBoiling()
{
    delete ui;
}
