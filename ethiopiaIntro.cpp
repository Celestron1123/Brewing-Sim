#include "ethiopiaIntro.h"
#include "ui_ethiopiaIntro.h"
#include "mainwindow.h"
#include <QPainter>

EthiopiaIntro::EthiopiaIntro(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EthiopiaIntro)
    , currentTextIndex(0)
{
    ui->setupUi(this);

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if (mainWindow) {
        connect(this, &EthiopiaIntro::goToBrew, mainWindow, &MainWindow::startEthiopia);
    }

    background = QPixmap(":/Resources/ethiopiaBackgronud.png");

    QFont font = ui->scrollText->font();
    font.setPointSize(7);
    ui->scrollText->setFont(font);

    scrollTexts << "T’ej is Ethiopia’s traditional honey wine, a golden drink that dates back over a thousand years."
                << "It is crafted from a careful fermentation of raw honey, fresh spring water, and the leaves and stems of a bittering plant called gesho—a botanical cousin of hops."
                << "In ancient times, T’ej was reserved for emperors and warriors, served during royal feasts and religious festivals."
                << "More than a beverage, it was a symbol of celebration, reverence, and craftsmanship."
                << "Today, T’ej continues to play an essential role in Ethiopian culture—shared at weddings, holidays, and gatherings, carrying the aroma of tradition.";

    updateScrollText();
}

EthiopiaIntro::~EthiopiaIntro()
{
    delete ui;
}

void EthiopiaIntro::on_beginBrewButton_clicked() {
    emit goToBrew();
}

void EthiopiaIntro::on_nextButton_clicked()
{
    if (currentTextIndex + 1 < scrollTexts.size()) {
        currentTextIndex++;
        updateScrollText();
    }
}

void EthiopiaIntro::on_prevButton_clicked()
{
    if (currentTextIndex > 0) {
        currentTextIndex--;
        updateScrollText();
    }
}

void EthiopiaIntro::updateScrollText()
{
    ui->scrollText->setText(scrollTexts[currentTextIndex]);
    ui->prevButton->setEnabled(currentTextIndex > 0);
    ui->nextButton->setEnabled(currentTextIndex < scrollTexts.size() - 1);

    QFont font = ui->scrollText->font();
    font.setPointSize(7);
    ui->scrollText->setFont(font);
}


void EthiopiaIntro::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), background);
}
