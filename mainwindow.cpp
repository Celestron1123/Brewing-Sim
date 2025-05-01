#include "mainwindow.h"
#include "caribbeanboiling.h"
#include "caribbeanbottling.h"
#include "caribbeandistillation.h"
#include "caribbeanfermentation.h"
#include "caribbeanharvest.h"
#include "caribbeanintro.h"
#include "caribbeanmaturation.h"
#include "creditswindow.h"
#include "japan.h"
#include "japanintro.h"
#include "japanpresspast.h"
#include "japanoutro.h"
#include "brazil.h"
#include "brazilintro.h"
#include "brazilharvest.h"
#include "brazilpresspast.h"
#include "braziloutro.h"
#include "germanyintro.h"
#include "germanymalt.h"
#include "germanyhop.h"
#include "germanymill.h"
#include "germanymash.h"
#include "germanylaut.h"
#include "germanyferment.h"
#include "germanymature.h"
#include "germanybottle.h"
#include "startwindow.h"
#include "ui_mainwindow.h"
#include "ethiopiaIntro.h"
#include "ethiopiaphysics.h"
#include "ethiopiaoutro.h"
#include "mexicointro.h"
#include "mexicoharvest.h"
#include "mexicocookpress.h"
#include "mexico.h"
#include "mexicooutro.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Install eventFilters for country highlighting
    ui->caribbeanButton->installEventFilter(this);
    ui->japanButton->installEventFilter(this);
    ui->brazilButton->installEventFilter(this);
    ui->mexicoButton->installEventFilter(this);
    ui->ethiopiaButton->installEventFilter(this);
    ui->germanyButton->installEventFilter(this);

    // Make buttons invisible to user
    ui->caribbeanButton->setStyleSheet("background: transparent; border: none;");
    ui->japanButton->setStyleSheet("background: transparent; border: none;");
    ui->brazilButton->setStyleSheet("background: transparent; border: none;");
    ui->mexicoButton->setStyleSheet("background: transparent; border: none;");
    ui->ethiopiaButton->setStyleSheet("background: transparent; border: none;");
    ui->germanyButton->setStyleSheet("background: transparent; border: none;");

    // Create a stack of widgets to hold all the pages in the main window
    widgetStack = new QStackedWidget(this);

    StartWindow *startWindow = new StartWindow(this);
    // index 0 - Start Window
    widgetStack->addWidget(startWindow);
    // index 1 - Main Window
    widgetStack->addWidget(ui->centralwidget);

    // Japan //
    Japan *japanWindow = new Japan(this);
    JapanIntro *japanIntroWindow = new JapanIntro(this);
    JapanPressPast *japanPressWindow = new JapanPressPast(this);
    JapanOutro *japanOutroWindow = new JapanOutro(this);
    Brazil *brazilWindow = new Brazil(this);
    BrazilIntro *brazilIntroWindow = new BrazilIntro(this);
    brazilHarvest *brazilHarvestWindow = new brazilHarvest(this);
    BrazilPressPast *brazilPressWindow = new BrazilPressPast(this);
    BrazilOutro *brazilOutroWindow = new BrazilOutro(this);

    // Caribbean //
    CaribbeanIntro *caribbeanIntroWindow = new CaribbeanIntro(this);
    CaribbeanHarvest *caribbeanHarvestWindow = new CaribbeanHarvest(this);
    CaribbeanBoiling *caribbeanBoilingWindow = new CaribbeanBoiling(this);
    CaribbeanFermentation *caribbeanFermentationWindow = new CaribbeanFermentation(this);
    CaribbeanDistillation *caribbeanDistillationWindow = new CaribbeanDistillation(this);
    CaribbeanMaturation *caribbeanMaturationWindow = new CaribbeanMaturation(this);
    CaribbeanBottling *caribbeanBottlingWindow = new CaribbeanBottling(this);

    // Germany //
    GermanyIntro *germanyIntroWindow = new GermanyIntro(this);
    GermanyMalt *germanyMaltWindow = new GermanyMalt(this);
    GermanyMill *germanyMillWindow = new GermanyMill(this);
    GermanyMash *germanyMashWindow = new GermanyMash(this);
    GermanyLaut *germanyLautWindow = new GermanyLaut(this);
    GermanyHop *germanyHopWindow = new GermanyHop(this);
    GermanyFerment *germanyFermentWindow = new GermanyFerment(this);
    GermanyMature *germanyMatureWindow = new GermanyMature(this);
    GermanyBottle *germanyBottleWindow = new GermanyBottle(this);

    // Ethiopia //
    EthiopiaIntro *ethiopiaWindow = new EthiopiaIntro(this);
    ethiopiaphysics *ethiopiaPhysicsWindow = new ethiopiaphysics(this);
    ethiopiaoutro *ethiopioOutroWindow = new ethiopiaoutro(this);

    // Mexico //
    MexicoIntro *mexicoIntroWindow = new MexicoIntro(this);
    MexicoHarvest *mexicoHarvestWindow = new MexicoHarvest(this);
    MexicoCookPress *mexicoCookWindow = new MexicoCookPress(this);
    Mexico *mexico = new Mexico(this);
    MexicoOutro *mexicoOutro = new MexicoOutro(this);

    //-------Japan Widgets-------
    // Adding the Japan window (index 2)
    widgetStack->addWidget(japanWindow);
    // Adding the Japan intro window (index 3)
    widgetStack->addWidget(japanIntroWindow);
    // Adding the Japan press window (index 4)
    widgetStack->addWidget(japanPressWindow);
    // Adding the Japan outro window (index 5)
    widgetStack->addWidget(japanOutroWindow);

    //-------Ethiopia Widgets-------
    // Adding the Ethiopia window (index 6)
    widgetStack->addWidget(ethiopiaWindow);
    // Index 7
    widgetStack->addWidget(ethiopiaPhysicsWindow);
    // Index 8
    widgetStack->addWidget(ethiopioOutroWindow);

    //-------Germany Widgets-------
    // Adding the Germany intro window (index 9)
    widgetStack->addWidget(germanyIntroWindow);
    // Adding the Germany Malt window (index 10)
    widgetStack->addWidget(germanyMaltWindow);
    // Adding the Germany Mill window (index 11)
    widgetStack->addWidget(germanyMillWindow);
    // Adding the Germany Mash window (index 12)
    widgetStack->addWidget(germanyMashWindow);
    // Adding the Germany Laut window (index 13)
    widgetStack->addWidget(germanyLautWindow);
    // Adding the Germany Hop window (index 14)
    widgetStack->addWidget(germanyHopWindow);
    // Adding the Germany Ferment window (index 15)
    widgetStack->addWidget(germanyFermentWindow);
    // Adding the Germany Mature window (index 16)
    widgetStack->addWidget(germanyMatureWindow);
    // Adding the Germany Bottle window (index 17)
    widgetStack->addWidget(germanyBottleWindow);

    //-------Caribbean Widgets-------
    // Adding the CaribbeanIntro window (index 18)
    widgetStack->addWidget(caribbeanIntroWindow);
    // Adding the CaribbeanHarvest window (index 19)
    widgetStack->addWidget(caribbeanHarvestWindow);
    // Adding the CaribbeanBoiling window (index 20)
    widgetStack->addWidget(caribbeanBoilingWindow);
    // Adding the CaribbeanFermentation window (index 21);
    widgetStack->addWidget(caribbeanFermentationWindow);
    // Adding the CaribbeanDistillation window (index 22);
    widgetStack->addWidget(caribbeanDistillationWindow);
    // Adding the CaribbeanMaturation window (index 23);
    widgetStack->addWidget(caribbeanMaturationWindow);
    // Adding the CaribbeanBottling window (index 24);
    widgetStack->addWidget(caribbeanBottlingWindow);

    //-----Mexico Widgets-------
    // Adding the Mexico intro window (index 25)
    widgetStack->addWidget(mexicoIntroWindow);
    // Adding the Mexico harvest window (index 26)
    widgetStack->addWidget(mexicoHarvestWindow);
    // Adding the Mexico cook and press window (index 27)
    widgetStack->addWidget(mexicoCookWindow);
    // Adding the Mexico window (index 28)
    widgetStack->addWidget(mexico);
    // Adding the Mexico outro window (index 29)
    widgetStack->addWidget(mexicoOutro);

    //-------Brazil Widgets-------
    // Adding the BrazilIntro window (index 30)
    widgetStack->addWidget(brazilIntroWindow);
    // Adding the Brazil Harvest window (index 31)
    widgetStack->addWidget(brazilHarvestWindow);
    // Adding the Brazil window (index 32)
    widgetStack->addWidget(brazilWindow);
    // Adding the Brazil Press window (index 33)
    widgetStack->addWidget(brazilPressWindow);
    // Adding the Brazil Outro window (index 34)
    widgetStack->addWidget(brazilOutroWindow);

    // Add credits window
    CreditsWindow *creditsWindow = new CreditsWindow(this);
    widgetStack->addWidget(creditsWindow);

    // After all countries are added, the stack is set as the central widget
    setCentralWidget(widgetStack);

    // Connections
    //---Japan Connections
    connect(this,
            &MainWindow::japanStart,
            japanWindow,
            &Japan::startPhysics);



    //---Caribbean Connections
    connect(this,
            &MainWindow::caribbeanBoilingStart,
            caribbeanBoilingWindow,
            &CaribbeanBoiling::startPhysics);

    connect(this,
            &MainWindow::caribbeanFermentationStart,
            caribbeanFermentationWindow,
            &CaribbeanFermentation::startPhysics);

    //---Germany Connections
    connect(this,
            &MainWindow::germanyHopStart,
            germanyHopWindow,
            &GermanyHop::startPhysics);

    //---Ethiopia Connections
    connect(this,
            &MainWindow::ethiopiaStart,
            ethiopiaPhysicsWindow,
            &ethiopiaphysics::startPhysics);

    connect(ethiopiaPhysicsWindow,
            &ethiopiaphysics::goToOutro,
            this,
            &MainWindow::startEthiopiaOutro);

    //---Mexico Connections
    connect(ui->mexicoButton,
            &QPushButton::clicked,
            this,
            &MainWindow::onMexicoButtonClicked);

    connect(this,
            &MainWindow::mexicoPhysicsStart,
            mexico,
            &Mexico::startPhysics);

    //---Brazil Connections
    connect(this,
            &MainWindow::brazilStart,
            brazilWindow,
            &Brazil::startPhysics);

    // Make sure window can't be resized
    setFixedSize(size());

    // Create a media player for japan
    audioPlayer = new QMediaPlayer(this);
    japanOutput = new QAudioOutput(this);

    // Create a media player for ethiopia & caribbean
    ethiopiaAudio = new QAudioOutput(this);
    rumAudio = new QAudioOutput(this);
    mexAudio = new QAudioOutput(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::returnToMain()
{
    audioPlayer->stop();
    widgetStack->setCurrentIndex(1);
}

void MainWindow::goToStart() {
    widgetStack->setCurrentIndex(0);
}

void MainWindow::goToCredits() {
    widgetStack->setCurrentIndex(35);
}

void MainWindow::on_backButton_clicked()
{
    widgetStack->setCurrentIndex(0);
}

void MainWindow::on_japanButton_clicked()
{
    widgetStack->setCurrentIndex(3);
    audioPlayer->setAudioOutput(japanOutput);
    audioPlayer->setSource(QUrl("qrc:/Resources/hateno.mp3"));
    japanOutput->setVolume(0.5);
    audioPlayer->play();
}

void MainWindow::startJapan()
{
    // Access japan window and replace it
    QWidget *oldJapan = widgetStack->widget(2);
    widgetStack->removeWidget(oldJapan);
    oldJapan->deleteLater();
    Japan *newJapan = new Japan(this);
    widgetStack->insertWidget(2, newJapan);

    connect(this,
            &MainWindow::japanStart,
            newJapan,
            &Japan::startPhysics);

    widgetStack->setCurrentIndex(2);
    emit japanStart();
}

void MainWindow::startJapanPress()
{
    // Access japan press window
    QWidget *oldJapanPress = widgetStack->widget(4);
    widgetStack->removeWidget(oldJapanPress);
    oldJapanPress->deleteLater();
    JapanPressPast *newJapanPress = new JapanPressPast(this);
    widgetStack->insertWidget(4, newJapanPress);

    widgetStack->setCurrentIndex(4);
}

void MainWindow::startJapanOutro()
{
    // Access japan outro window
    QWidget *oldJapanOutro = widgetStack->widget(5);
    widgetStack->removeWidget(oldJapanOutro);
    oldJapanOutro->deleteLater();
    JapanOutro *newJapanOutro = new JapanOutro(this);
    widgetStack->insertWidget(5, newJapanOutro);

    widgetStack->setCurrentIndex(5);
}

void MainWindow::on_ethiopiaButton_clicked()
{
    // Replace old intro
    QWidget *oldIntro = widgetStack->widget(6);
    widgetStack->removeWidget(oldIntro);
    oldIntro->deleteLater();

    EthiopiaIntro *newIntro = new EthiopiaIntro(this);
    widgetStack->insertWidget(6, newIntro);

    // Connect its goToBrew signal
    connect(newIntro, &EthiopiaIntro::goToBrew, this, &MainWindow::startEthiopia);

    // Music
    audioPlayer->setAudioOutput(ethiopiaAudio);
    audioPlayer->setSource(QUrl("qrc:/Resources/ethiopiaSoundtrack.mp3"));
    ethiopiaAudio->setVolume(0.05);
    audioPlayer->play();

    widgetStack->setCurrentIndex(6);
}

void MainWindow::startEthiopia()
{
    QWidget *oldPhysics = widgetStack->widget(7);
    widgetStack->removeWidget(oldPhysics);
    oldPhysics->deleteLater();
    ethiopiaphysics *newPhysics = new ethiopiaphysics(this);
    widgetStack->insertWidget(7, newPhysics);
    connect(this, &MainWindow::ethiopiaStart, newPhysics, &ethiopiaphysics::startPhysics);

    widgetStack->setCurrentIndex(7);
    emit ethiopiaStart();
}

void MainWindow::startEthiopiaOutro()
{
    QWidget *oldOutro = widgetStack->widget(8);
    widgetStack->removeWidget(oldOutro);
    oldOutro->deleteLater();
    ethiopiaoutro *newOutro = new ethiopiaoutro(this);
    widgetStack->insertWidget(8, newOutro);

    widgetStack->setCurrentIndex(8);
}

void MainWindow::on_germanyButton_clicked()
{
    widgetStack->setCurrentIndex(9);
}

void MainWindow::startGMalt()
{
    widgetStack->setCurrentIndex(10);
}

void MainWindow::startGMill()
{
    widgetStack->setCurrentIndex(11);
}

void MainWindow::startGMash()
{
    widgetStack->setCurrentIndex(12);
}

void MainWindow::startGLaut()
{
    widgetStack->setCurrentIndex(13);
}

void MainWindow::startGHop()
{
    // Access Germany Hop window and replace it
    QWidget *oldGHop = widgetStack->widget(14);
    widgetStack->removeWidget(oldGHop);
    oldGHop->deleteLater();
    GermanyHop *newGHop = new GermanyHop(this);
    widgetStack->insertWidget(14, newGHop);

    connect(this,
            &MainWindow::germanyHopStart,
            newGHop,
            &GermanyHop::startPhysics);

    widgetStack->setCurrentIndex(14);
    emit germanyHopStart();
}

void MainWindow::startGFerment()
{
    widgetStack->setCurrentIndex(15);
}

void MainWindow::startGMat()
{
    widgetStack->setCurrentIndex(16);
}

void MainWindow::startGBottle()
{
    widgetStack->setCurrentIndex(17);
}

void MainWindow::on_caribbeanButton_clicked()
{
    widgetStack->setCurrentIndex(18);
    audioPlayer->setAudioOutput(rumAudio);
    audioPlayer->setSource(QUrl("qrc:/Resources/BosunBill.mp3"));
    rumAudio->setVolume(1.5);
    audioPlayer->play();
}

void MainWindow::startCaribbean()
{
    widgetStack->setCurrentIndex(19);
}

void MainWindow::startCaribbeanBoiling()
{
    widgetStack->setCurrentIndex(20);
    emit caribbeanBoilingStart();
}

void MainWindow::startCaribbeanFermentation()
{
    widgetStack->setCurrentIndex(21);
    emit caribbeanFermentationStart();
}

void MainWindow::startCaribbeanDistillation()
{
    widgetStack->setCurrentIndex(22);
}

void MainWindow::startCaribbeanMaturation()
{
    widgetStack->setCurrentIndex(23);
}

void MainWindow::startCaribbeanBottling()
{
    widgetStack->setCurrentIndex(24);
}

void MainWindow::onMexicoButtonClicked(){

    audioPlayer->setAudioOutput(mexAudio);
    audioPlayer->setSource(QUrl("qrc:/Resources/mexguitar.mp3"));
    mexAudio->setVolume(0.5);
    audioPlayer->play();
    widgetStack->setCurrentIndex(25);
}

void MainWindow::startMexicoHarvest(){
    QWidget *oldMexicoHarvest = widgetStack->widget(26);
    widgetStack->removeWidget(oldMexicoHarvest);
    oldMexicoHarvest->deleteLater();
    MexicoHarvest *newMexicoHarvest = new MexicoHarvest(this);
    widgetStack->insertWidget(26, newMexicoHarvest);

    widgetStack->setCurrentIndex(26);
}

void MainWindow::startMexicoCook(){
    QWidget *oldMexicoCook = widgetStack->widget(27);
    widgetStack->removeWidget(oldMexicoCook);
    oldMexicoCook->deleteLater();
    MexicoCookPress *newMexicoCookPress = new MexicoCookPress(this);
    widgetStack->insertWidget(27, newMexicoCookPress);

    widgetStack->setCurrentIndex(27);
}

void MainWindow::startMexicoMix(){
    QWidget *oldMexico = widgetStack->widget(28);
    widgetStack->removeWidget(oldMexico);
    oldMexico->deleteLater();
    Mexico *newMexico = new Mexico(this);
    widgetStack->insertWidget(28, newMexico);

    connect(this,
            &MainWindow::mexicoPhysicsStart,
            newMexico,
            &Mexico::startPhysics);

    widgetStack->setCurrentIndex(28);
    emit mexicoPhysicsStart();
}

void MainWindow::startMexicoOutro(){
    QWidget *oldMexicoOutro = widgetStack->widget(29);
    widgetStack->removeWidget(oldMexicoOutro);
    oldMexicoOutro->deleteLater();
    MexicoOutro *newMexicoOutro = new MexicoOutro(this);
    widgetStack->insertWidget(29, newMexicoOutro);

    widgetStack->setCurrentIndex(29);
}

void MainWindow::on_brazilButton_clicked()
{
    widgetStack->setCurrentIndex(30);
}

void MainWindow::startBrazilHarvest()
{
    widgetStack->setCurrentIndex(31);
}

void MainWindow::startBrazil() {
    widgetStack->setCurrentIndex(32);
    emit brazilStart();
}

void MainWindow::startBrazilPress()
{
    widgetStack->setCurrentIndex(33);
}

void MainWindow::startBrazilOutro()
{
    widgetStack->setCurrentIndex(34);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->brazilButton && (event->type() == QEvent::Enter))
    {
        ui->worldMap->setPixmap(QPixmap(":/Resources/brazilHighlighted.jpg"));
        ui->worldMap->setScaledContents(true);
    }
    else if (event->type() == QEvent::Leave)
    {
        ui->worldMap->setPixmap(QPixmap(":/Resources/worldMap.jpg"));
        ui->worldMap->setScaledContents(true);
    }

    if (obj == ui->caribbeanButton && (event->type() == QEvent::Enter))
    {
        ui->worldMap->setPixmap(QPixmap(":/Resources/caribbeanHighlighted.jpg"));
        ui->worldMap->setScaledContents(true);
    }
    else if (event->type() == QEvent::Leave)
    {
        ui->worldMap->setPixmap(QPixmap(":/Resources/worldMap.jpg"));
        ui->worldMap->setScaledContents(true);
    }

    if (obj == ui->japanButton && (event->type() == QEvent::Enter))
    {
        ui->worldMap->setPixmap(QPixmap(":/Resources/japanHighlighted.jpg"));
        ui->worldMap->setScaledContents(true);
    }
    else if (event->type() == QEvent::Leave)
    {
        ui->worldMap->setPixmap(QPixmap(":/Resources/worldMap.jpg"));
        ui->worldMap->setScaledContents(true);
    }

    if (obj == ui->mexicoButton && (event->type() == QEvent::Enter))
    {
        ui->worldMap->setPixmap(QPixmap(":/Resources/mexicoHighlighted.jpg"));
        ui->worldMap->setScaledContents(true);
    }
    else if (event->type() == QEvent::Leave)
    {
        ui->worldMap->setPixmap(QPixmap(":/Resources/worldMap.jpg"));
        ui->worldMap->setScaledContents(true);
    }

    if (obj == ui->ethiopiaButton && (event->type() == QEvent::Enter))
    {
        ui->worldMap->setPixmap(QPixmap(":/Resources/ethiopiaHighlighted.jpg"));
        ui->worldMap->setScaledContents(true);
    }
    else if (event->type() == QEvent::Leave)
    {
        ui->worldMap->setPixmap(QPixmap(":/Resources/worldMap.jpg"));
        ui->worldMap->setScaledContents(true);
    }

    if (obj == ui->germanyButton && (event->type() == QEvent::Enter))
    {
        ui->worldMap->setPixmap(QPixmap(":/Resources/germanyHighlighted.jpg"));
        ui->worldMap->setScaledContents(true);
    }
    else if (event->type() == QEvent::Leave)
    {
        ui->worldMap->setPixmap(QPixmap(":/Resources/worldMap.jpg"));
        ui->worldMap->setScaledContents(true);
    }

    return false;
}
