#include "japanintro.h"
#include "ui_japanintro.h"
#include "mainwindow.h"

JapanIntro::JapanIntro(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::JapanIntro)
{
    ui->setupUi(this);

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if(mainWindow) {
        connect(this,
                &JapanIntro::goToBrew,
                mainWindow,
                &MainWindow::startJapan);
    }
}

JapanIntro::~JapanIntro()
{
    delete ui;
}

void JapanIntro::on_start_clicked()
{
    emit goToBrew();
}

