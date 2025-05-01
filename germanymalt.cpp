/**
 * The implementation of GermanyMalt
 *
 * @author Ryan Hamerman
 * @date 04/24/2025
 */

#include "germanymalt.h"
#include "ui_germanymalt.h"
#include "mainwindow.h"

GermanyMalt::GermanyMalt(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GermanyMalt)
{
    ui->setupUi(this);

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if(mainWindow) {
        connect(this,
                &GermanyMalt::goToGMill,
                mainWindow,
                &MainWindow::startGMill);
    }
}

GermanyMalt::~GermanyMalt()
{
    delete ui;
}

void GermanyMalt::on_continueButton_clicked()
{
    emit goToGMill();
}
