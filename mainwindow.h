#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QAudioOutput>
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_japanButton_clicked();
    void on_ethiopiaButton_clicked();
    void on_caribbeanButton_clicked();
    void on_brazilButton_clicked();
    void on_germanyButton_clicked();
    void onMexicoButtonClicked();

    void on_backButton_clicked();

public slots:
    void startJapan();
    void startGMalt();
    void startGMill();
    void startGMash();
    void startGLaut();
    void startGHop();
    void startGFerment();
    void startGMat();
    void startGBottle();
    void startJapanPress();
    void startJapanOutro();
    void startCaribbean();
    void startCaribbeanBoiling();
    void startCaribbeanFermentation();
    void startCaribbeanDistillation();
    void startCaribbeanMaturation();
    void startCaribbeanBottling();
    void startMexicoHarvest();
    void startMexicoCook();
    void startMexicoMix();
    void startMexicoOutro();

    void returnToMain();
    void goToStart();
    void goToCredits();

    void startEthiopia(); // physics
    void startEthiopiaOutro();

    void startBrazil();
    void startBrazilHarvest();
    void startBrazilPress();
    void startBrazilOutro();

signals:
    void japanStart();
    void brazilStart();
    void caribbeanBoilingStart();
    void caribbeanFermentationStart();
    void germanyHopStart();
    void ethiopiaStart();
    void mexicoPhysicsStart();

private:
    Ui::MainWindow *ui;
    QStackedWidget *widgetStack;
    bool eventFilter(QObject *object, QEvent *event);
    QMediaPlayer *audioPlayer;
    QAudioOutput *japanOutput;
    QAudioOutput *ethiopiaAudio;
    QAudioOutput *rumAudio;
    QAudioOutput *mexAudio;
};
#endif // MAINWINDOW_H
