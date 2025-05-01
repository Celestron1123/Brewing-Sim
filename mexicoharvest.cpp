#include "mexicoharvest.h"
#include "ui_mexicoharvest.h"
#include "mainwindow.h"

MexicoHarvest::MexicoHarvest(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MexicoHarvest)
{
    ui->setupUi(this);
    ui->continueBtn->setEnabled(false);

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if(mainWindow) {
        connect(this,
                &MexicoHarvest::goToCook,
                mainWindow,
                &MainWindow::startMexicoCook);
    }

    connect(ui->continueBtn,&QPushButton::clicked,this,&MexicoHarvest::onContinueClicked);
    connect(ui->agave1btn, &QPushButton::clicked, this, &MexicoHarvest::onAgaveOneClicked);
    connect(ui->agave2btn, &QPushButton::clicked, this, &MexicoHarvest::onAgaveTwoClicked);
    connect(ui->agave3btn, &QPushButton::clicked, this, &MexicoHarvest::onAgaveThreeClicked);
}

MexicoHarvest::~MexicoHarvest()
{
    delete ui;
}

void MexicoHarvest::onAgaveOneClicked()
{
    QPixmap newPixmap(":/Resources/agavepina.png");
    ui->agave1->setPixmap(newPixmap);
    ui->agave1->setGeometry(50, 350, 211, 221);
    agave1Clicked = true;
    checkAllAgavesClicked();
}
void MexicoHarvest::onAgaveTwoClicked()
{
    QPixmap newPixmap(":/Resources/agavepina.png");
    ui->agave2->setPixmap(newPixmap);
    ui->agave2->setGeometry(400, 370, 221, 241);
    agave2Clicked = true;
    checkAllAgavesClicked();
}
void MexicoHarvest::onAgaveThreeClicked()
{
    QPixmap newPixmap(":/Resources/agavepina.png");
    ui->agave3->setPixmap(newPixmap);
    ui->agave3->setGeometry(770, 270, 201, 221);
    agave3Clicked = true;
    checkAllAgavesClicked();
}

void MexicoHarvest::checkAllAgavesClicked()
{
    if (agave1Clicked && agave2Clicked && agave3Clicked) {
        ui->continueBtn->setEnabled(true);
    }
}

void MexicoHarvest::onContinueClicked(){
    emit goToCook();
}
