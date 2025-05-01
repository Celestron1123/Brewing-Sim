#ifndef GERMANYINTRO_H
#define GERMANYINTRO_H

/**
 * The introduction screen for the Germany Experience. Contains signals and slots for moving through other windows
 *
 * @author Ryan Hamerman
 * @date 04/24/25
 */

#include <QWidget>

namespace Ui {
class GermanyIntro;
}

/**
 * @brief Class representing the introduction screen for the Germany experience
 */
class GermanyIntro : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the GermanyIntro with a given model
     *
     * @param parent Pointer to the parent window
     */
    explicit GermanyIntro(QWidget *parent = nullptr);

    /**
     * @brief Destructor for GermanyIntro
     */
    ~GermanyIntro();

private:
    /**
     * @brief Pointer to the UI object that holds the layout and widgets of GermanyIntro
     */
    Ui::GermanyIntro *ui;

private slots:
    /**
     * @brief Recives signal that the start button has been pressed, sending a signal to MainWindow to move to the next scene
     */
    void on_startButton_clicked();

signals:
    /**
     * @brief Signal sent to MainWindow to move to next scene
     */
    void goToGMalt();
};

#endif // GERMANYINTRO_H
