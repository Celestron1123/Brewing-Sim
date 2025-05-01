// Author - William Ngo
// Date - 4/19/25
// Header class for the intro of the ehtiopia world.
#ifndef ETHIOPIAINTRO_H
#define ETHIOPIAINTRO_H

#include <QWidget>
#include <QPixmap>
#include <QStringList>

namespace Ui {
class EthiopiaIntro;
}

class EthiopiaIntro : public QWidget
{
    Q_OBJECT

public:
    // Constructor: Initializes the intro widget with an optional parent
    explicit EthiopiaIntro(QWidget *parent = nullptr);

    // Destructor: Cleans up resources
    ~EthiopiaIntro();

private slots:
    // Triggered when the user clicks "Begin Brewing"
    // Emits a signal to transition to the next game phase
    void on_beginBrewButton_clicked();

    // Triggered when the user clicks the "Next" button
    // Advances to the next piece of scroll text
    void on_nextButton_clicked();

    // Triggered when the user clicks the "Previous" button
    // Goes back to the previous piece of scroll text
    void on_prevButton_clicked();

signals:
    // Signal emitted when the player chooses to begin the brewing process
    void goToBrew();

private:
    Ui::EthiopiaIntro *ui;        // Pointer to the UI elements defined in the .ui file
    QPixmap background;           // Holds the background image of the scene

    QStringList scrollTexts;      // List of text entries for scrolling through the narrative
    int currentTextIndex;         // Tracks the currently displayed text index

    // Updates the on-screen text to reflect the currentTextIndex
    void updateScrollText();

protected:
    // Reimplemented paint event to custom-draw the background or other visuals
    void paintEvent(QPaintEvent *event) override;
};

#endif // ETHIOPIAINTRO_H

