/**
 * The implementation of CaribbeanHarvest
 *
 * @author Steven Luo
 * @date 04/24/2025
 */

#include "caribbeanharvest.h"
#include "ui_caribbeanharvest.h"
#include "mainwindow.h"

CaribbeanHarvest::CaribbeanHarvest(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CaribbeanHarvest)
{
    ui->setupUi(this);

    // Set cursor icon to be a scythe
    QPixmap scytheIcon(":/Resources/scytheIcon.png");
    QPixmap scaledScytheIcon = scytheIcon.scaled(48, 48, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QCursor scytheCursor(scaledScytheIcon, 15, 10);
    this->setCursor(scytheCursor);

    // Set cursor icon when clicking sugar cane to be a tilted scythe
    QPixmap scytheIconClicked(":/Resources/scytheIconClicked.png");
    QPixmap scaledScytheIconClicked = scytheIconClicked.scaled(48, 48, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QCursor scytheCursorClicked(scaledScytheIconClicked, 15, 10);

    // Connect pressed and released signals to change cursor icon
    connect(ui->harvestButton, &QPushButton::pressed, this, [=]() {
        this->setCursor(scytheCursorClicked);
    });

    connect(ui->harvestButton, &QPushButton::released, this, [=]() {
        this->setCursor(scytheCursor);
    });

    connect(ui->harvestButton_2, &QPushButton::pressed, this, [=]() {
        this->setCursor(scytheCursorClicked);
    });

    connect(ui->harvestButton_2, &QPushButton::released, this, [=]() {
        this->setCursor(scytheCursor);
    });

    connect(ui->harvestButton_3, &QPushButton::pressed, this, [=]() {
        this->setCursor(scytheCursorClicked);
    });

    connect(ui->harvestButton_3, &QPushButton::released, this, [=]() {
        this->setCursor(scytheCursor);
    });

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if(mainWindow) {
        connect(this,
                &CaribbeanHarvest::goToBoiling,
                mainWindow,
                &MainWindow::startCaribbeanBoiling);
    }
}

void CaribbeanHarvest::on_harvestButton_clicked()
{
    ui->sugarCane->setPixmap(QPixmap(":/Resources/cutSugarCaneRum.png"));
    ui->sugarCane->setScaledContents(true);
}


void CaribbeanHarvest::on_harvestButton_2_clicked()
{
    ui->sugarCane_2->setPixmap(QPixmap(":/Resources/cutSugarCaneRum.png"));
    ui->sugarCane_2->setScaledContents(true);
}


void CaribbeanHarvest::on_harvestButton_3_clicked()
{
    ui->sugarCane_3->setPixmap(QPixmap(":/Resources/cutSugarCaneRum.png"));
    ui->sugarCane_3->setScaledContents(true);
}


void CaribbeanHarvest::on_continueButton_clicked()
{
    emit goToBoiling();
}

CaribbeanHarvest::~CaribbeanHarvest()
{
    delete ui;
}
