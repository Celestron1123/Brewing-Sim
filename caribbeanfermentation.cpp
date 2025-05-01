/**
 * The implementation of CaribbeanFermentation
 *
 * @author Steven Luo
 * @date 04/24/2025
 */

#include "caribbeanfermentation.h"
#include "ui_caribbeanfermentation.h"
#include "Box2D/Dynamics/b2Body.h"
#include "qpainter.h"
#include "mainwindow.h"
#include <QMouseEvent>

CaribbeanFermentation::CaribbeanFermentation(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CaribbeanFermentation)
    , world(b2Vec2(0.0f, -10.0f))
    , timer()
{
    ui->setupUi(this);

    // Install event filter
    ui->pourButton->installEventFilter(this);
    ui->pourButton->setAttribute(Qt::WA_Hover, true);
    ui->pourButton->setMouseTracking(true);
    // Make pour button (valve on hanging molasses barrel) invisible to user
    ui->pourButton->setStyleSheet("background: transparent; border: none;");

    background = QPixmap(":/Resources/rumBackgroundFermentation.png");
    table = QPixmap(":/Resources/smallTable.png");
    bowl = QPixmap(":/Resources/bowl.png");
    barrel = QPixmap(":/Resources/emptyFermentationBarrel.png");
    barrelFront = QPixmap(":/Resources/emptyFermentationBarrelFront.png");
    molassesBarrelHanging = QPixmap(":/Resources/molassesBarrelHanging.png");
    molassesPourStream = QPixmap(":/Resources/molassesPourStream.png");

    // Dimensions for play-box
    float worldWidth = 111.5f;
    float worldHeight = 60.0f;

    // Create a ground/static body for boundaries
    b2BodyDef wallDef;
    wallDef.position.Set(0.0f, -30.0f);
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

    // Top table wall
    {
        b2PolygonShape topTableWall;
        topTableWall.SetAsBox(worldWidth/11.5, 1.5f, b2Vec2(-28.5f, 15.0f), 0);
        wallBody->CreateFixture(&topTableWall, 0.0f);
    }

    // Left table leg wall
    {
        b2PolygonShape leftTableLeg;
        leftTableLeg.SetAsBox(1.0f, worldWidth/13.5, b2Vec2(-36.0f, 5.5f), 0);
        wallBody->CreateFixture(&leftTableLeg, 0.0f);
    }

    // Right table leg wall
    {
        b2PolygonShape rightTableLegUnderBarrel;
        rightTableLegUnderBarrel.SetAsBox(1.0f, worldWidth/13.5, b2Vec2(-21.0f, 5.5f), 0);
        wallBody->CreateFixture(&rightTableLegUnderBarrel, 0.0f);
    }

    // Top table wall under barrel
    {
        b2PolygonShape topTableWallUnderBarrel;
        topTableWallUnderBarrel.SetAsBox(worldWidth/11.5, 1.5f, b2Vec2(10.0f, 5.0f), 0);
        wallBody->CreateFixture(&topTableWallUnderBarrel, 0.0f);
    }

    // Left table leg wall under barrel
    {
        b2PolygonShape leftTableLegUnderBarrel;
        leftTableLegUnderBarrel.SetAsBox(1.0f, worldWidth/13.5, b2Vec2(2.5f, -4.5f), 0);
        wallBody->CreateFixture(&leftTableLegUnderBarrel, 0.0f);
    }

    // Right table leg wall under barrel
    {
        b2PolygonShape rightTableLegUnderBarrel;
        rightTableLegUnderBarrel.SetAsBox(1.0f, worldWidth/13.5, b2Vec2(17.5f, -4.5f), 0);
        wallBody->CreateFixture(&rightTableLegUnderBarrel, 0.0f);
    }

    // Right yeast bowl wall
    {
        b2PolygonShape rightYeastBowlWall;
        rightYeastBowlWall.SetAsBox(4.0f, 0.5f, b2Vec2(-31.5f, 18.5f), -60.0f);
        wallBody->CreateFixture(&rightYeastBowlWall, 0.0f);
    }

    // Left yeast bowl wall
    {
        b2PolygonShape leftYeastBowlWall;
        leftYeastBowlWall.SetAsBox(4.0f, 0.5f, b2Vec2(-25.5f, 18.5f), 60.0f);
        wallBody->CreateFixture(&leftYeastBowlWall, 0.0f);
    }

    // Left fermentation barrel
    {
        b2PolygonShape leftBarrel;
        leftBarrel.SetAsBox(1.0f, 10.0f, b2Vec2(1.0f, 18.0f), 0);
        wallBody->CreateFixture(&leftBarrel, 0.0f);
    }

    // Right fermentation barrel
    {
        b2PolygonShape rightBarrel;
        rightBarrel.SetAsBox(1.0f, 10.0f, b2Vec2(19.0f, 18.0f), 0);
        wallBody->CreateFixture(&rightBarrel, 0.0f);
    }

    // Bottom fermentation barrel
    {
        b2PolygonShape bottomBarrel;
        bottomBarrel.SetAsBox(9.0f, 2.0f, b2Vec2(10.0f, 8.0f), 0);
        wallBody->CreateFixture(&bottomBarrel, 0.0f);
    }

    // Lets us use wallBody's properties in other methods
    groundBody = wallBody;

    b2BodyDef yeastDef;
    yeastDef.type = b2_dynamicBody;
    float xPosYeast = -33.0f;
    float yPosYeast = -9.0f;
    for (int i = 0.0f; i < 4; i++)
    {
        yeastDef.position.Set(xPosYeast, yPosYeast);
        b2Body* cell = world.CreateBody(&yeastDef);

        // Define the circle shape representing the ball
        b2CircleShape circleShape;
        circleShape.m_radius = 0.7f;

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
    connect(&timer, &QTimer::timeout, this, &CaribbeanFermentation::updateTime);

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if(mainWindow) {
        connect(this,
                &CaribbeanFermentation::goToDistillation,
                mainWindow,
                &MainWindow::startCaribbeanDistillation);
    }
}

void CaribbeanFermentation::startPhysics()
{
    timer.start();
}

void CaribbeanFermentation::updateTime() {
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    world.Step(timeStep, velocityIterations, positionIterations);

    if (isYeastInFermentationBarrel() && isPoured) {
        ui->beginFermentationButton->setEnabled(true);
    } else {
        ui->beginFermentationButton->setEnabled(false);
    }

    update();
}

b2Vec2 CaribbeanFermentation::screenToWorld(const QPoint &point) {
    const float scale = 10.0f;
    float worldX = (point.x() - width()/2) / scale;
    float worldY = (height()/2 - point.y()) / scale;
    return b2Vec2(worldX, worldY);
}

void CaribbeanFermentation::mousePressEvent(QMouseEvent *event) {
    b2Vec2 clickPoint = screenToWorld(event->pos());
    // Check if the mouse click is on a ball's fixture
    for (auto cell : yeast)
    {
        if (cell->GetFixtureList()->TestPoint(clickPoint)) {
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

void CaribbeanFermentation::mouseMoveEvent(QMouseEvent *event) {
    if (mouseJoint) {
        b2Vec2 worldPoint = screenToWorld(event->pos());
        mouseJoint->SetTarget(worldPoint);
    }
}

void CaribbeanFermentation::mouseReleaseEvent(QMouseEvent *) {
    if (mouseJoint) {
        world.DestroyJoint(mouseJoint);
        mouseJoint = nullptr;
    }
}

void CaribbeanFermentation::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen(Qt::black);
    pen.setWidth(4);
    painter.setPen(pen);
    const float scale = 10.0f;

    // Draw background
    painter.drawPixmap(0, 0, width(), height(), background);

    // Draw small table
    painter.drawPixmap(150, 380, width()/4.5, height()/2, table);

    // Draw bowl
    painter.drawPixmap(185, 360, width()/6, height()/6, bowl);

    // Draw small table
    painter.drawPixmap(537, 480, width()/4.5, height()/2, table);

    // Draw pot or pot boiling
    painter.drawPixmap(520, 280, width()/4, width()/4, barrel);

    // Draw molasses pour stream when it is prompted
    if (isPouring) {
        painter.drawPixmap(567, 169, width()/6, width()/4, molassesPourStream);
    }

    // Draw hanging molasses barrel
    painter.drawPixmap(400, -50, width()/4, width()/4, molassesBarrelHanging);

    // Draw yeast
    for (auto cell : yeast)
    {
        b2Vec2 pos = cell->GetPosition();
        float radius = 0.7f;

        float screenX = width() / 2 + pos.x * scale;
        float screenY = height() / 2 - pos.y * scale;

        painter.setBrush(QColorConstants::Svg::orange);
        painter.drawEllipse(QPointF(screenX, screenY), radius * scale, radius * scale);
    }

    // Draw front of pot
    painter.drawPixmap(520, 280, width()/4, width()/4, barrelFront);
}

bool CaribbeanFermentation::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->pourButton && (event->type() == QEvent::Enter)) {
        molassesBarrelHanging = QPixmap(":/Resources/molassesBarrelHangingHighlighted.png");
        ui->pourText->show();
        ui->pourText->setText("Pour");
    } else if (event->type() == QEvent::Leave) {
        molassesBarrelHanging = QPixmap(":/Resources/molassesBarrelHanging.png");
        ui->pourText->hide();
    }
    return false;
}

void CaribbeanFermentation::on_pourButton_clicked()
{
    isPouring = true;
    pourCountdownValue = 3;
    molassesBarrelHanging = QPixmap(":/Resources/molassesBarrelHangingHighlighted.png");

    ui->pourButton->hide();

    // Start pouring animation text
    ui->pourText->setText("Pouring.");
    ui->pourText->show();

    connect(&pourCountdownTimer, &QTimer::timeout, this, [this]() {
        pourCountdownValue--;

        if (pourCountdownValue == 2) {
            ui->pourText->setText("Pouring..");
        } else if (pourCountdownValue == 1) {
            ui->pourText->setText("Pouring...");
        } else if (pourCountdownValue == 0) {
            ui->pourText->setText("Done!");
        } else {
            isPouring = false;
            isPoured = true;
            pourCountdownTimer.stop();
            molassesBarrelHanging = QPixmap(":/Resources/molassesBarrelHanging.png");
            barrel = QPixmap(":/Resources/filledMolassesFermentationBarrel.png");
            ui->pourText->hide();
        }
    });

    pourCountdownTimer.start(1000);
}

void CaribbeanFermentation::on_beginFermentationButton_clicked()
{
    fermentationCountdownValue = 3;
    ui->fermentCountdownText->setText("Fermenting.");
    ui->fermentCountdownText->show();
    yeast.clear();
    ui->beginFermentationButton->setEnabled(false);
    barrel = QPixmap(":/Resources/bubblingFermentationBarrel.png");

    connect(&fermentationCountdownTimer, &QTimer::timeout, this, [this]() {
        fermentationCountdownValue--;

        if (fermentationCountdownValue == 2) {
            ui->fermentCountdownText->setText("Fermenting..");
        } else if (fermentationCountdownValue == 1) {
            ui->fermentCountdownText->setText("Fermenting...");
        } else if (fermentationCountdownValue == 0) {
            ui->fermentCountdownText->setText("Done!");
        } else {
            fermentationCountdownTimer.stop();
            ui->fermentCountdownText->hide();
            ui->beginFermentationButton->hide();
            barrel = QPixmap(":/Resources/foamyFermentationBarrel.png");
        }
    });

    fermentationCountdownTimer.start(1000);
}

bool CaribbeanFermentation::isYeastInFermentationBarrel() const {
    auto isInsideBarrel = [](const b2Body* body) {
        b2Vec2 pos = body->GetPosition();
        return pos.x > 1.0f && pos.x < 19.0f && pos.y > -22.0f && pos.y < -2.0f;
    };

    if (yeast.empty()) {
        return false;
    }

    for (const b2Body* cell : yeast) {
        if (!isInsideBarrel(cell)) {
            return false;
        }
    }
    return true;
}

void CaribbeanFermentation::on_continueButton_clicked()
{
    emit goToDistillation();
}

CaribbeanFermentation::~CaribbeanFermentation()
{
    delete ui;
}

