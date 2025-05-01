#include "mexicooutro.h"
#include "ui_mexicooutro.h"
#include "mainwindow.h"

MexicoOutro::MexicoOutro(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MexicoOutro)
{
    ui->setupUi(this);

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if(mainWindow) {
        connect(this,
                &MexicoOutro::goToMain,
                mainWindow,
                &MainWindow::returnToMain);

        connect(ui->mainBtn, &QPushButton::clicked, this, &MexicoOutro::onBtnClicked);
        connect(ui->pour, &QPushButton::clicked, this, &MexicoOutro::onPourClicked);
    }
}

MexicoOutro::~MexicoOutro()
{
    delete ui;
}

void MexicoOutro::onPourClicked(){
    QPixmap newPixmap(":/Resources/mexbottle.png");
    ui->emptyBottle->setPixmap(newPixmap);
    ui->emptyBottle->setGeometry(725, 455, 101, 221);
}

void MexicoOutro::onBtnClicked()
{
    emit goToMain();
}
