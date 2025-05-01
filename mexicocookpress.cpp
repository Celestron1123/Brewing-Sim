#include "mexicocookpress.h"
#include "ui_mexicocookpress.h"
#include "mainwindow.h"

MexicoCookPress::MexicoCookPress(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MexicoCookPress)
{
    ui->setupUi(this);
    ui->steam->hide();
    ui->ovenclosed->hide();
    ui->continuebtn->setDisabled(true);

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if(mainWindow) {
        connect(this,
                &MexicoCookPress::goToMix,
                mainWindow,
                &MainWindow::startMexicoMix);
    }

    connect(ui->steambtn, &QPushButton::clicked, this, &MexicoCookPress::onSteamerClicked);
    connect(ui->presser, &QSlider::valueChanged, this, &MexicoCookPress::adjustPosition);
    connect(ui->continuebtn,&QPushButton::clicked,this,&MexicoCookPress::onContinueClicked);
}

MexicoCookPress::~MexicoCookPress()
{
    delete ui;
}

void MexicoCookPress::onSteamerClicked(){

    if(!ovenIsClosed){
        ui->steam->show();
        ui->oven->hide();
        ui->ovenclosed->show();
        ovenIsClosed = true;
    }
    else{
        ui->steam->hide();
        ui->oven->show();
        ui->ovenclosed->hide();
        ovenIsClosed = false;
    }

    int value = ui->presser->value();
    if (value > 98 && ovenIsClosed)
    {
        ui->continuebtn->setDisabled(false);
    }
    else
    {
        ui->continuebtn->setDisabled(true);
    }

}

void MexicoCookPress::adjustPosition(int value)
{
    ui->press->move(660, 70 + (value * 1.5));
    if (value > 98 && ovenIsClosed)
    {
        ui->continuebtn->setDisabled(false);
    }
    else
    {
        ui->continuebtn->setDisabled(true);
    }

    if(value > 75){
        ui->pina->hide();
        ui->pina_2->hide();
        ui->pina_3->hide();
    }else{
        ui->pina->show();
        ui->pina_2->show();
        ui->pina_3->show();
    }
}

void MexicoCookPress::onContinueClicked(){
    emit goToMix();
}
