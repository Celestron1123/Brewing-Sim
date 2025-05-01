/**
 * The implementation of GermanyMill
 *
 * @author Ryan Hamerman
 * @date 04/24/2025
 */

#include "germanymill.h"
#include "ui_germanymill.h"
#include "mainwindow.h"

GermanyMill::GermanyMill(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GermanyMill)
{
    ui->setupUi(this);

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if(mainWindow) {
        connect(this,
                &GermanyMill::goToGMash,
                mainWindow,
                &MainWindow::startGMash);
    }
}

GermanyMill::~GermanyMill()
{
    delete ui;
}

void GermanyMill::on_continueButton_clicked()
{
    emit goToGMash();
}
