/**
 * The implementation of GermanyBottle
 *
 * @author Ryan Hamerman
 * @date 04/24/2025
 */

#include "germanybottle.h"
#include "ui_germanybottle.h"
#include "mainwindow.h"

GermanyBottle::GermanyBottle(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GermanyBottle)
{
    ui->setupUi(this);

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if(mainWindow) {
        connect(this,
                &GermanyBottle::goToMain,
                mainWindow,
                &MainWindow::returnToMain);
    }
}

GermanyBottle::~GermanyBottle()
{
    delete ui;
}

void GermanyBottle::on_continueButton_clicked()
{
    emit goToMain();
}
