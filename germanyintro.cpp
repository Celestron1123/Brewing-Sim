/**
 * The implementation of GermanyIntro
 *
 * @author Ryan Hamerman
 * @date 04/24/2025
 */

#include "germanyintro.h"
#include "ui_germanyintro.h"
#include "mainwindow.h"

GermanyIntro::GermanyIntro(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GermanyIntro)
{
    ui->setupUi(this);

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if(mainWindow) {
        connect(this,
                &GermanyIntro::goToGMalt,
                mainWindow,
                &MainWindow::startGMalt);
    }
}

GermanyIntro::~GermanyIntro()
{
    delete ui;
}

void GermanyIntro::on_startButton_clicked()
{
    emit goToGMalt();
}
