#include "ethiopiaphysics.h"
#include "ui_ethiopiaphysics.h"
#include "mainwindow.h"

ethiopiaphysics::ethiopiaphysics(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ethiopiaphysics)
    , world(b2Vec2(0.0f, -10.0f))
    , timer()
{
    ui->setupUi(this);

    explanationText =
        "Welcome to Tej Brewing!\n\n"
        "Step 1: Add Gesho (Ethiopian hops) to your clay pot. These add flavor and act as a preservative.\n\n"
        "Step 2: Pour in the honey. Use lots of it — Tej is sweet and strong!\n\n"
        "Step 3: Sprinkle in the yeast. It will ferment the sugars into alcohol.\n\n"
        "Step 4: Let it ferment for several days in a warm, dark place.\n\n"
        "Tej is a traditional Ethiopian honey wine. It's often homebrewed and served during holidays and special occasions.\n\n"
        "Tip: Drop each ingredient into the clay pot to start the process!";

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if(mainWindow) {
        connect(this, &ethiopiaphysics::goToOutro, mainWindow, &MainWindow::startEthiopiaOutro);
    }

    background = QPixmap(":/Resources/ethiopiaBackgronud.png");
    table = QPixmap(":/Resources/ethiopiaTable.png");
    bowl = QPixmap(":/Resources/ethiopiaBowl.png");
    claypot = QPixmap(":/Resources/ethiopiaClayPot.png");
    claypotfront = QPixmap(":/Resources/ethiopiaClayPotFront.png");
    lid = QPixmap(":/Resources/ethiopiaLod.png");
    calendarImage = QPixmap(":/Resources/ethiopiaCalendar.png");
    xMark = QPixmap(":/Resources/ethiopiaxMark.png");

    float worldWidth = 100.0f;
    float worldHeight = 50.0f;

    b2BodyDef wallDef;
    wallDef.position.Set(0.0f, -25.0f);
    b2Body* wallBody = world.CreateBody(&wallDef);

    b2PolygonShape shape;

    // Outer walls
    shape.SetAsBox(0.5f, worldHeight / 2, b2Vec2(-worldWidth / 2 - 0.5f, worldHeight / 2 + 2.0f), 0);
    wallBody->CreateFixture(&shape, 0.0f);
    shape.SetAsBox(0.5f, worldHeight / 2, b2Vec2(worldWidth / 2 + 0.5f, worldHeight / 2 + 2.0f), 0);
    wallBody->CreateFixture(&shape, 0.0f);
    shape.SetAsBox(worldWidth / 2, 0.5f, b2Vec2(0, worldHeight + 0.5f + 2.0f), 0);
    wallBody->CreateFixture(&shape, 0.0f);
    shape.SetAsBox(worldWidth / 2, 0.5f, b2Vec2(0, 11.0f + 2.0f), 0); // floor
    wallBody->CreateFixture(&shape, 0.0f);


    // ---------------- CLAYPOT WALLS ----------------

    // Base remains the same
    shape.SetAsBox(8.5f, 0.5f, b2Vec2(0.0f, 0.0f), 0);
    wallBody->CreateFixture(&shape, 0.0f);

    // Left claypot wall
    shape.SetAsBox(0.2f, 35.0f, b2Vec2(-4.9f, 2.0f), 0);
    wallBody->CreateFixture(&shape, 0.0f);

    // Right claypot wall
    shape.SetAsBox(0.2f, 35.0f, b2Vec2(4.9f, 2.0f), 0);
    wallBody->CreateFixture(&shape, 0.0f);


    // ---------------- BOWL BASES ----------------
    // Left Bowl base
    shape.SetAsBox(5.5f, 2.5f, b2Vec2(-37.5f, 12.0f), 0);
    wallBody->CreateFixture(&shape, 0.0f);

    // Center Bowl base
    shape.SetAsBox(5.5f, 2.5f, b2Vec2(-21.5f, 12.0f), 0);
    wallBody->CreateFixture(&shape, 0.0f);

    // Right Bowl Base
    shape.SetAsBox(5.5f, 2.5f, b2Vec2(22.5f, 12.0f), 0);
    wallBody->CreateFixture(&shape, 0.0f);


    // ---------------- BOWL WALLS  ----------------

    float height = 18.0f;
    int y = 0;


    // Center Bowl
    shape.SetAsBox(0.2f, height, b2Vec2(-26.0f, y), 0);  // Left wall
    wallBody->CreateFixture(&shape, 0.0f);
    shape.SetAsBox(0.2f, height, b2Vec2(-17.0f, y), 0);  // Right wall
    wallBody->CreateFixture(&shape, 0.0f);
    // Left Bowl
    shape.SetAsBox(0.2f, height, b2Vec2(-42.0f, y), 0);  // Left wall
    wallBody->CreateFixture(&shape, 0.0f);
    shape.SetAsBox(0.2f, height, b2Vec2(-32.0f, y), 0);  // Right wall
    wallBody->CreateFixture(&shape, 0.0f);
    // Right Bowl
    shape.SetAsBox(0.2f, height, b2Vec2(18.0f, y), 0);   // Left wall
    wallBody->CreateFixture(&shape, 0.0f);
    shape.SetAsBox(0.2f, height, b2Vec2(27.0f, y), 0);   // Right wall
    wallBody->CreateFixture(&shape, 0.0f);

    calendarTimer.setInterval(900);
    connect(&calendarTimer, &QTimer::timeout, this, [this]() {
        xDaysMarked++;
        if (xDaysMarked >= 30) {
            calendarTimer.stop();
            waitFinished = true;
            waitingInProgress = false;

            ui->lidButton->setEnabled(false);
            ui->waitButton->setEnabled(false);
            ui->shortcutButton->setEnabled(false);
            ui->nextButton->setEnabled(true);
        }
        update();
    });
    ui->lidButton->setEnabled(false);
    ui->waitButton->setEnabled(false);
    ui->nextButton->setEnabled(false);

    groundBody = wallBody;

    b2BodyDef def;
    def.type = b2_dynamicBody;
    b2CircleShape circle;
    b2FixtureDef fix;
    fix.density = 1.0f;
    fix.friction = 0.3f;

    float xG = -25.0f, yG = 20.0f;
    for (int i = 0; i < 6; ++i) {
        def.position.Set(xG, yG);
        b2Body* body = world.CreateBody(&def);
        circle.m_radius = 1.0f;
        fix.shape = &circle;
        body->CreateFixture(&fix);
        gesho.push_back(body);
        xG += 3.0f;
        if (xG > -19.0f) {
            xG = -25.0f;
            yG += 3.0f;
        }
    }

    float xY = 19.0f, yY = 20.0f;
    for (int i = 0; i < 8; ++i) {
        def.position.Set(xY, yY);
        b2Body* body = world.CreateBody(&def);
        circle.m_radius = 0.5f;
        fix.shape = &circle;
        body->CreateFixture(&fix);
        yeast.push_back(body);
        xY += 3.0f;
        if (xY > 25.0f) {
            xY = 19.0f;
            yY += 3.0f;
        }
    }

    float xH = -40.0f, yH = 20.0f;
    for (int i = 0; i < 3; ++i) {
        def.position.Set(xH, yH);
        b2Body* body = world.CreateBody(&def);
        circle.m_radius = 1.5f;
        fix.shape = &circle;
        body->CreateFixture(&fix);
        honey.push_back(body);
        xH += 6.0f;
        if (xH > -34.0f) {
            xH = -40.0f;
            yH -= 4.0f;
        }
    }

    connect(ui->shortcutButton, &QPushButton::clicked, this, &ethiopiaphysics::on_shortcutButton_clicked);

    connect(ui->nextButton, &QPushButton::clicked, this, &ethiopiaphysics::on_nextButton_clicked);

    connect(ui->lidButton, &QPushButton::clicked, this, [this]() {
        if (waitingInProgress) return;

        lidON = !lidON;
        ui->lidButton->setText(lidON ? "Lid Off" : "Lid On");

        if (lidON && ingredientsInPot()) {
            ui->waitButton->setEnabled(true);
        } else {
            ui->waitButton->setEnabled(false);
        }

        update();
    });

    connect(ui->waitButton, &QPushButton::clicked, this, [this]() {
        if (waitingInProgress) return;

        showCalendar = true;
        xDaysMarked = 0;
        waitFinished = false;
        ui->nextButton->setEnabled(false);
        waitingInProgress = true;

        ui->lidButton->setText("Lid On");
        ui->lidButton->setEnabled(false);
        ui->waitButton->setEnabled(false);

        calendarTimer.start(100);
    });
    timer.setInterval(10);
    connect(&timer, &QTimer::timeout, this, &ethiopiaphysics::updateTime);
    QLabel* explanationLabel = new QLabel(this);
    explanationLabel->setText(explanationText);
    explanationLabel->setWordWrap(true);
    explanationLabel->setGeometry(10, 10, 400, 275);
    explanationLabel->setStyleSheet(
        "color: white;"
        "background: qlineargradient("
        "x1:0, y1:0, x2:0, y2:1,"
        "stop:0 rgba(100, 100, 100, 100),"
        "stop:1 rgba(30, 30, 30, 220)"
        ");"
        "border-radius: 20px;"
        "padding: 5px;"
        );

    QString buttonStyle = R"(
QPushButton {
    background-color: white;
    color: black;
    border: 2px solid #4e342e;
    border-radius: 6px;
    padding: 6px;
    font: bold 14pt "Georgia";
}
QPushButton:hover {
    background-color: #a96f4d;
}
QPushButton:disabled {
    background-color: #dddddd;
    color: gray;
    border: 2px solid #999999;
}
)";
    ui->lidButton->setStyleSheet(buttonStyle);
    ui->waitButton->setStyleSheet(buttonStyle);
    ui->nextButton->setStyleSheet(buttonStyle);
    ui->shortcutButton->setStyleSheet(buttonStyle);

}


ethiopiaphysics::~ethiopiaphysics() {
    delete ui;
}

void ethiopiaphysics::startPhysics() {
    timer.start();
}

void ethiopiaphysics::updateTime() {
    world.Step(1.0f / 60.0f, 6, 2);

    if (!waitingInProgress && !waitFinished) {
        if (ingredientsInPot()) {
            ui->lidButton->setEnabled(true);
            if (lidON) {
                ui->waitButton->setEnabled(true);
            }
        }
    }

    update();
}

b2Vec2 ethiopiaphysics::screenToWorld(const QPoint &point) {
    const float scale = 10.0f;
    float worldX = (point.x() - width()/2) / scale;
    float worldY = (height()/2 - point.y()) / scale;
    return b2Vec2(worldX, worldY);
}

void ethiopiaphysics::mousePressEvent(QMouseEvent *event) {
    b2Vec2 clickPoint = screenToWorld(event->pos());
    for (auto item : gesho) {
        if (item->GetFixtureList() && item->GetFixtureList()->TestPoint(clickPoint)) {
            b2MouseJointDef md;
            md.bodyA = groundBody;
            md.bodyB = item;
            md.target = clickPoint;
            md.maxForce = 1000.0f * item->GetMass();
            md.collideConnected = true;
            mouseJoint = (b2MouseJoint*) world.CreateJoint(&md);
            return;
        }
    }
    for (auto item : yeast) {
        if (item->GetFixtureList() && item->GetFixtureList()->TestPoint(clickPoint)) {
            b2MouseJointDef md;
            md.bodyA = groundBody;
            md.bodyB = item;
            md.target = clickPoint;
            md.maxForce = 1000.0f * item->GetMass();
            md.collideConnected = true;
            mouseJoint = (b2MouseJoint*) world.CreateJoint(&md);
            return;
        }
    }
    for (auto item : honey) {
        if (item->GetFixtureList() && item->GetFixtureList()->TestPoint(clickPoint)) {
            b2MouseJointDef md;
            md.bodyA = groundBody;
            md.bodyB = item;
            md.target = clickPoint;
            md.maxForce = 1000.0f * item->GetMass();
            md.collideConnected = true;
            mouseJoint = (b2MouseJoint*) world.CreateJoint(&md);
            return;
        }
    }
}

void ethiopiaphysics::mouseMoveEvent(QMouseEvent *event) {
    if (mouseJoint) {
        mouseJoint->SetTarget(screenToWorld(event->pos()));
    }
}

void ethiopiaphysics::mouseReleaseEvent(QMouseEvent *event) {
    Q_UNUSED(event);
    if (mouseJoint) {
        world.DestroyJoint(mouseJoint);
        mouseJoint = nullptr;
    }
}

void ethiopiaphysics::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen(Qt::black);
    pen.setWidth(4);
    painter.setPen(pen);

    painter.drawPixmap(0, 0, width(), height(), background);
    painter.drawPixmap(0, 225, width(), height(), table);
    painter.drawPixmap(100, 350, width()/6, height()/6, bowl);
    painter.drawPixmap(250, 350, width()/6, height()/6, bowl);
    painter.drawPixmap(690, 350, width()/6, height()/6, bowl);
    painter.drawPixmap(420, 165, width()/4, width()/4, claypot);

    const float scale = 10.0f;
    auto drawBodies = [&](const std::vector<b2Body*>& list, QColor color, float radius) {
        painter.setBrush(color);
        for (auto body : list) {
            b2Vec2 pos = body->GetPosition();
            float screenX = width() / 2 + pos.x * scale;
            float screenY = height() / 2 - pos.y * scale;
            painter.drawEllipse(QPointF(screenX, screenY), radius * scale, radius * scale);
        }
    };

    drawBodies(gesho, QColorConstants::Svg::brown, 1.0);
    drawBodies(yeast, QColorConstants::Svg::yellow, 0.5);
    drawBodies(honey, QColor(255, 253, 208), 1.5);

    // Draw claypot front to simulate "depth"
    painter.drawPixmap(420, 165, width()/4, width()/4, claypotfront);

    if(lidON){
        painter.drawPixmap(480, 93, width()/7, width()/6, lid);
    }

    painter.drawPixmap(820, 150, width()/5, width()/5, calendarImage);
    int calX = 820;  // wherever you draw your calendar
    int calY = 150;
    painter.drawPixmap(calX, calY, width() / 5, width() / 5, calendarImage);

    int startX = calX + 49;
    int startY = calY + 85;
    int cellW = 20;
    int cellH = 20;

    for (int i = 0; i < xDaysMarked && i < 30; ++i) {
        int row, col;

        if (i < 4) {             // First row (days 1–4)
            row = 0;
            col = i + 3;         // Shifted 3 columns to the right
        } else if (i < 11) {     // Second row (days 5–11)
            row = 1;
            col = i - 4;
        } else if (i < 18) {     // Third row (days 12–18)
            row = 2;
            col = i - 11;
        } else if (i < 25) {     // Fourth row (days 19–25)
            row = 3;
            col = i - 18;
        } else {                 //
            row = 4;
            col = i - 25;
        }

        int x = startX + col * cellW;
        int y = startY + row * cellH;
        int xOffset = (cellW - 24) / 2;
        int yOffset = (cellH - 16) / 2;
        painter.drawPixmap(x + xOffset, y + yOffset, 13, 13, xMark);
    }
}

void ethiopiaphysics::on_nextButton_clicked() {
    if (waitFinished) {
        emit goToOutro();
    }
}
bool ethiopiaphysics::ingredientsInPot() const {
    auto isInsidePot = [](const b2Body* body) {
        b2Vec2 pos = body->GetPosition();
        return pos.x > -5.1f && pos.x < 5.1f && pos.y < 35.0f;
    };

    for (b2Body* g : gesho)
        if (!isInsidePot(g)) return false;
    for (b2Body* h : honey)
        if (!isInsidePot(h)) return false;
    for (b2Body* y : yeast)
        if (!isInsidePot(y)) return false;

    return true;
}

void ethiopiaphysics::on_shortcutButton_clicked() {
    // Move all balls into the claypot instantly
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

    placeBodies(gesho);
    placeBodies(honey);
    placeBodies(yeast);

    ui->lidButton->setEnabled(true);

    if (lidON) {
        ui->waitButton->setEnabled(true);
    }

    update();
}

