/**
 * Distillation window for Brazil.
 *
 * @authors Julia Maia
 * @date 04/24/2025
 *
 * Checked by Julia Maia
 */

#include "brazilpresspast.h"
#include "ui_brazilpresspast.h"
#include "mainwindow.h"

BrazilPressPast::BrazilPressPast(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BrazilPressPast)
{
    ui->setupUi(this);

    ui->flame->hide();
    ui->steam->hide();

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if(mainWindow) {
        // Connect to main and display the outro window
        connect(this,
                &BrazilPressPast::goToOutro,
                mainWindow,
                &MainWindow::startBrazilOutro); }
}

BrazilPressPast::~BrazilPressPast()
{
    delete ui;
}

void BrazilPressPast::on_heat_clicked()
{
    ui->flame->show();
    ui->steam->show();
}


void BrazilPressPast::on_continueButton_clicked()
{
    emit goToOutro();
}
