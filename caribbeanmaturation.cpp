/**
 * The implementation of CaribbeanMaturation
 *
 * @author Steven Luo
 * @date 04/24/2025
 */

#include "caribbeanmaturation.h"
#include "ui_caribbeanmaturation.h"
#include "qpainter.h"
#include "mainwindow.h"

CaribbeanMaturation::CaribbeanMaturation(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CaribbeanMaturation)
{
    ui->setupUi(this);

    background = QPixmap(":/Resources/rumBackgroundDistillation.png");
    barrels = QPixmap(":/Resources/rumMaturationBarrels.png");

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if(mainWindow) {
        connect(this,
                &CaribbeanMaturation::goToBottling,
                mainWindow,
                &MainWindow::startCaribbeanBottling);
    }
}

void CaribbeanMaturation::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen(Qt::black);
    pen.setWidth(4);
    painter.setPen(pen);

    // Draw background
    painter.drawPixmap(0, 0, width(), height(), background);

    // Draw barrels
    painter.drawPixmap(290, 320, width()/2, width()/4, barrels);

    // Draw rum aged banner based on slider value
    if (ui->matureButton->isHidden()) {
        int agingValue = ui->agingSlider->value();
        if (agingValue == 1) {
            rumAgedBanner = QPixmap(":/Resources/rumAgedBannerYear1.png");
        } else if (agingValue == 2) {
            rumAgedBanner = QPixmap(":/Resources/rumAgedBannerYear3.png");
        } else {
            rumAgedBanner = QPixmap(":/Resources/rumAgedBannerYear5.png");
        }

        painter.drawPixmap(290, 150, width()/2, width()/5.4, rumAgedBanner);
    }

}

void CaribbeanMaturation::on_matureButton_clicked()
{
    matureCountdownValue = 3;
    ui->matureCountdownText->setText("Maturing.");
    ui->matureCountdownText->show();
    ui->matureButton->setEnabled(false);
    ui->sliderText->hide();
    ui->agingSlider->hide();
    ui->year1->hide();
    ui->year3->hide();
    ui->year5->hide();

    connect(&matureCountdownTimer, &QTimer::timeout, this, [this]() {
        matureCountdownValue--;

        if (matureCountdownValue == 2) {
            ui->matureCountdownText->setText("Maturing..");
        } else if (matureCountdownValue == 1) {
            ui->matureCountdownText->setText("Maturing...");
        } else if (matureCountdownValue == 0) {
            ui->matureCountdownText->setText("Maturing....");
        } else {
            matureCountdownTimer.stop();
            ui->matureCountdownText->hide();
            ui->matureButton->hide();
            update();
        }
    });

    matureCountdownTimer.start(1000);
}

void CaribbeanMaturation::on_continueButton_clicked()
{
    emit goToBottling();
}

CaribbeanMaturation::~CaribbeanMaturation()
{
    delete ui;
}
