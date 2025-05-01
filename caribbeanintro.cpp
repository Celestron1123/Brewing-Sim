/**
 * The implementation of CaribbeanIntro
 *
 * @author Steven Luo
 * @date 04/24/2025
 */

#include "caribbeanintro.h"
#include "ui_caribbeanintro.h"
#include "mainwindow.h"

CaribbeanIntro::CaribbeanIntro(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CaribbeanIntro)
{
    ui->setupUi(this);

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if(mainWindow) {
        connect(this,
                &CaribbeanIntro::goToHarvest,
                mainWindow,
                &MainWindow::startCaribbean);
    }
}

void CaribbeanIntro::on_start_clicked()
{
    emit goToHarvest();
}

CaribbeanIntro::~CaribbeanIntro()
{
    delete ui;
}
