/**
 * The implementation of CaribbeanDistillation
 *
 * @author Steven Luo
 * @date 04/24/2025
 */

#include "caribbeandistillation.h"
#include "ui_caribbeandistillation.h"
#include "qpainter.h"
#include "mainwindow.h"

CaribbeanDistillation::CaribbeanDistillation(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CaribbeanDistillation)
{
    ui->setupUi(this);

    background = QPixmap(":/Resources/rumBackgroundDistillation.png");
    potStill = QPixmap(":/Resources/potStill.png");

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if(mainWindow) {
        connect(this,
                &CaribbeanDistillation::goToMaturation,
                mainWindow,
                &MainWindow::startCaribbeanMaturation);
    }
}

void CaribbeanDistillation::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen(Qt::black);
    pen.setWidth(4);
    painter.setPen(pen);

    // Draw background
    painter.drawPixmap(0, 0, width(), height(), background);

    // Draw pot still
    painter.drawPixmap(320, 120, width()/2.2, width()/2.2, potStill);
}

void CaribbeanDistillation::on_distillButton_clicked()
{
    potStill = QPixmap(":/Resources/potStillFire.png");
    update();

    distillCountdownValue = 3;
    ui->distillCountdownText->setText("Distilling.");
    ui->distillCountdownText->show();
    ui->distillButton->setEnabled(false);

    connect(&distillCountdownTimer, &QTimer::timeout, this, [this]() {
        distillCountdownValue--;

        if (distillCountdownValue == 2) {
            ui->distillCountdownText->setText("Distilling..");
        } else if (distillCountdownValue == 1) {
            ui->distillCountdownText->setText("Distilling...");
        } else if (distillCountdownValue == 0) {
            ui->distillCountdownText->setText("Done!");
        } else {
            distillCountdownTimer.stop();
            ui->distillCountdownText->hide();
            ui->distillButton->hide();
            potStill = QPixmap(":/Resources/potStill.png");
            update();
        }
    });

    distillCountdownTimer.start(1000);
}

void CaribbeanDistillation::on_continueButton_clicked()
{
    emit goToMaturation();
}

CaribbeanDistillation::~CaribbeanDistillation()
{
    delete ui;
}
