/**
 * The implementation of GermanyMature
 *
 * @author Ryan Hamerman
 * @date 04/24/2025
 */

#include "germanymature.h"
#include "ui_germanymature.h"
#include "mainwindow.h"

GermanyMature::GermanyMature(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GermanyMature)
{
    ui->setupUi(this);

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if(mainWindow) {
        connect(this,
                &GermanyMature::goToGBottle,
                mainWindow,
                &MainWindow::startGBottle);
    }
}

GermanyMature::~GermanyMature()
{
    delete ui;
}

void GermanyMature::on_continueButton_clicked()
{
    emit goToGBottle();
}
