/**
 * The implementation of GermanyLaut
 *
 * @author Ryan Hamerman
 * @date 04/24/2025
 */

#include "germanylaut.h"
#include "ui_germanylaut.h"
#include "mainwindow.h"

GermanyLaut::GermanyLaut(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GermanyLaut)
{
    ui->setupUi(this);

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if(mainWindow) {
        connect(this,
                &GermanyLaut::goToGHop,
                mainWindow,
                &MainWindow::startGHop);
    }
}

GermanyLaut::~GermanyLaut()
{
    delete ui;
}

void GermanyLaut::on_continueButton_clicked()
{
    emit goToGHop();
}
