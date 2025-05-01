#include "mexicointro.h"
#include "ui_mexicointro.h"
#include "mainwindow.h"

MexicoIntro::MexicoIntro(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MexicoIntro)
{
    ui->setupUi(this);

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if(mainWindow) {
        connect(this,
                &MexicoIntro::goToHarvest,
                mainWindow,
                &MainWindow::startMexicoHarvest);
    }

    connect(ui->start, &QPushButton::clicked, this, &MexicoIntro::onStartClicked);
}

MexicoIntro::~MexicoIntro()
{
    delete ui;
}

void MexicoIntro::onStartClicked(){
    emit goToHarvest();
}
