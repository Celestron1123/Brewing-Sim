#include "japanoutro.h"
#include "ui_japanoutro.h"
#include "mainwindow.h"

JapanOutro::JapanOutro(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::JapanOutro)
{
    ui->setupUi(this);

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if(mainWindow) {
        connect(this,
                &JapanOutro::goToMain,
                mainWindow,
                &MainWindow::returnToMain);
    }
}

JapanOutro::~JapanOutro()
{
    delete ui;
}

void JapanOutro::on_pushButton_clicked()
{
    emit goToMain();
}


void JapanOutro::on_pour_clicked()
{
    ui->empty->setPixmap(QPixmap(":/Resources/sake.png"));
}

