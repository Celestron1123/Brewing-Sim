#include "ethiopiaoutro.h"
#include "ui_ethiopiaoutro.h"
#include "mainwindow.h"
#include <QPainter>
#include <QMouseEvent>

ethiopiaoutro::ethiopiaoutro(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ethiopiaoutro)
{
    ui->setupUi(this);

    background = QPixmap(":/Resources/ethiopiaBackgronud.png");
    claypotImg = QPixmap(":/Resources/ethiopiaClaypotFull.png");
    glassImg = QPixmap(":/Resources/ethiopiaGlass.png");
    glassFullImg = QPixmap(":/Resources/ethiopaFullGlass.png");
    tableImg = QPixmap(":/Resources/ethiopiaTable.png");

    filledCount = 0;

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if (mainWindow) {
        connect(this, &ethiopiaoutro::goToMain, mainWindow, &MainWindow::returnToMain);
    }

    connect(ui->finishButton, &QPushButton::clicked, this, [this]() {
        emit goToMain();
    });
}

ethiopiaoutro::~ethiopiaoutro()
{
    delete ui;
}

void ethiopiaoutro::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    int claypotW = 120;
    int claypotH = 150;
    int bottomMargin = 100;

    claypotRect = QRect(50, height() - claypotH - bottomMargin, claypotW, claypotH);
}

void ethiopiaoutro::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    painter.drawPixmap(0, 0, width(), height(), background);

    int tableW = width() / 2;
    int tableH = height() / 2;
    int tableX = 0;
    int tableY = height() - tableH + 95;

    painter.drawPixmap(tableX, tableY, tableW, tableH, tableImg);

    // Sizes
    int claypotW = 120;
    int claypotH = 150;
    int glassW = 60;
    int glassH = 100;
    int bottomMargin = 100;
    int spacing = 30;

    // Claypot
    claypotRect = QRect(50, height() - claypotH - bottomMargin, claypotW, claypotH);
    painter.drawPixmap(claypotRect, claypotImg);

    // Glasses
    int startX = claypotRect.right() + spacing;
    for (int i = 0; i < 3; ++i) {
        QRect glassRect(startX + i * (glassW + spacing), height() - glassH - bottomMargin, glassW, glassH);
        if (i < filledCount)
            painter.drawPixmap(glassRect, glassFullImg);
        else
            painter.drawPixmap(glassRect, glassImg);
    }
}

void ethiopiaoutro::mousePressEvent(QMouseEvent *event)
{
    if (claypotRect.contains(event->pos()) && filledCount < 3) {
        filledCount++;
        update();
    }
}

