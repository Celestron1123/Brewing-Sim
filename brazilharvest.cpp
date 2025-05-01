/**
 * Main brewing class for Brazil.
 *
 * @authors Steven Luo, Julia Maia, Elijah Potter
 * @date 04/24/2025
 *
 * Checked by Julia Maia
 */

#include "brazilharvest.h"
#include "ui_brazilharvest.h"
#include "mainwindow.h"

brazilHarvest::brazilHarvest(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::brazilHarvest)
{
    ui->setupUi(this);

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if(mainWindow) {
        connect(this,
                &brazilHarvest::goToBoiling,
                mainWindow,
                &MainWindow::startBrazil);
    }
}

brazilHarvest::~brazilHarvest()
{
    delete ui;
}

void brazilHarvest::on_harvestButton_clicked()
{
    ui->sugarcane->setPixmap(QPixmap(":/Resources/sugarcaneCut.png"));
    ui->sugarcane->setScaledContents(true);
}


void brazilHarvest::on_harvestButton2_clicked()
{
    ui->sugarcane2->setPixmap(QPixmap(":/Resources/sugarcaneCut.png"));
    ui->sugarcane2->setScaledContents(true);
}


void brazilHarvest::on_harvestButton3_clicked()
{
    ui->sugarcane3->setPixmap(QPixmap(":/Resources/sugarcaneCut.png"));
    ui->sugarcane3->setScaledContents(true);
}


void brazilHarvest::on_continueButton_clicked()
{
    emit goToBoiling();
}
