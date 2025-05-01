/**
 * Intro window for Brazil.
 *
 * @authors Julia Maia
 * @date 04/24/2025
 *
 * Checked by Julia Maia
 */

#include "brazilintro.h"
#include "ui_brazilintro.h"
#include "mainwindow.h"

BrazilIntro::BrazilIntro(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BrazilIntro)
{
    ui->setupUi(this);

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if(mainWindow) {
        connect(this,
                &BrazilIntro::goToHarvest,
                mainWindow,
                &MainWindow::startBrazilHarvest);
    }
}

BrazilIntro::~BrazilIntro()
{
    delete ui;
}

void BrazilIntro::on_start_clicked()
{
    emit goToHarvest();
}
