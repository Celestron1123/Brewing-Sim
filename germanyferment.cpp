/**
 * The implementation of GermanyFerment
 *
 * @author Ryan Hamerman
 * @date 04/24/2025
 */

#include "germanyferment.h"
#include "ui_germanyferment.h"
#include "mainwindow.h"

GermanyFerment::GermanyFerment(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GermanyFerment)
{
    ui->setupUi(this);

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if(mainWindow) {
        connect(this,
                &GermanyFerment::goToGMat,
                mainWindow,
                &MainWindow::startGMat);
    }
}

GermanyFerment::~GermanyFerment()
{
    delete ui;
}

void GermanyFerment::on_continueButton_clicked()
{
    emit goToGMat();
}
