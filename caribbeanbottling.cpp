/**
 * The implementation of CaribbeanBottling
 *
 * @author Steven Luo
 * @date 04/24/2025
 */

#include "caribbeanbottling.h"
#include "ui_caribbeanbottling.h"
#include "qpainter.h"
#include "mainwindow.h"

CaribbeanBottling::CaribbeanBottling(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CaribbeanBottling)
{
    ui->setupUi(this);

    background = QPixmap(":/Resources/rumBackgroundDistillation.png");
    bottleAndTable = QPixmap(":/Resources/emptyRumBottleTable.png");
    rumFinishedBanner = QPixmap(":/Resources/rumFinishedBanner.png");

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if(mainWindow) {
        connect(this,
                &CaribbeanBottling::goToMain,
                mainWindow,
                &MainWindow::returnToMain);
    }
}

void CaribbeanBottling::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen(Qt::black);
    pen.setWidth(4);
    painter.setPen(pen);

    // Draw background
    painter.drawPixmap(0, 0, width(), height(), background);

    // Draw bottle of rum and table
    painter.drawPixmap(400, 240, width()/3.2, width()/3, bottleAndTable);

    // Draw rum finished banner after bottleButton is clicked
    if (ui->bottleButton->isHidden()) {
        painter.drawPixmap(385, 120, width()/3, width()/11, rumFinishedBanner);
    }
}

void CaribbeanBottling::on_bottleButton_clicked()
{
    bottleAndTable = QPixmap(":/Resources/filledRumBottleTable.png");
    ui->bottleButton->hide();
    update();
}

void CaribbeanBottling::on_backToMapButton_clicked()
{
    emit goToMain();
}

CaribbeanBottling::~CaribbeanBottling()
{
    delete ui;
}
