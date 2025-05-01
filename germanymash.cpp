/**
 * The implementation of GermanyMash
 *
 * @author Ryan Hamerman
 * @date 04/24/2025
 */

#include "germanymash.h"
#include "ui_germanymash.h"
#include "mainwindow.h"

GermanyMash::GermanyMash(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GermanyMash)
{
    ui->setupUi(this);

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if(mainWindow) {
        connect(this,
                &GermanyMash::goToGLaut,
                mainWindow,
                &MainWindow::startGLaut);
    }
}

GermanyMash::~GermanyMash()
{
    delete ui;
}

void GermanyMash::on_continueButton_clicked()
{
    emit goToGLaut();
}
