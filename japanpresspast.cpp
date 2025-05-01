#include "japanpresspast.h"
#include "ui_japanpresspast.h"
#include "mainwindow.h"

JapanPressPast::JapanPressPast(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::JapanPressPast)
{
    ui->setupUi(this);
    ui->flame->hide();
    ui->steam->hide();
    ui->pushButton->setDisabled(true);
    buttonPressed = false;
    connect(ui->presser, &QSlider::valueChanged, this, &JapanPressPast::adjustPosition);

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if(mainWindow) {
        connect(this,
                &JapanPressPast::goToOutro,
                mainWindow,
                &MainWindow::startJapanOutro);
    }
}

JapanPressPast::~JapanPressPast()
{
    delete ui;
}

void JapanPressPast::adjustPosition(int value)
{
    ui->arm->move(330, -40 + (value * 1.5));
    if (value > 98 && buttonPressed)
    {
        ui->pushButton->setDisabled(false);
    }
    else
    {
        ui->pushButton->setDisabled(true);
    }
}


void JapanPressPast::on_pasteruizer_clicked()
{
    ui->flame->show();
    ui->steam->show();
    buttonPressed = true;
    int value = ui->presser->value();
    if (value > 98)
    {
        ui->pushButton->setDisabled(false);
    }
    else
    {
        ui->pushButton->setDisabled(true);
    }
}


void JapanPressPast::on_pushButton_clicked()
{
    emit goToOutro();
}

