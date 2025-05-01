#ifndef GERMANYMALT_H
#define GERMANYMALT_H

/**
 * The Malting screen for the Germany Experience. Contains signals and slots for moving through other windows
 *
 * @author Ryan Hamerman
 * @date 04/24/25
 */

#include <QWidget>

namespace Ui {
class GermanyMalt;
}

/**
 * @brief Class representing the Malting screen for the Germany experience
 */
class GermanyMalt : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the GermanyMalt with a given model
     *
     * @param parent Pointer to the parent window
     */
    explicit GermanyMalt(QWidget *parent = nullptr);

    /**
     * @brief Destructor for GermanyMalt
     */
    ~GermanyMalt();

private:
    /**
     * @brief Pointer to the UI object that holds the layout and widgets of GermanyMalt
     */
    Ui::GermanyMalt *ui;

private slots:
    /**
     * @brief Recives signal that the continue button has been pressed, sending a signal to MainWindow to move to the next scene
     */
    void on_continueButton_clicked();

signals:
    /**
     * @brief Signal sent to MainWindow to move to next scene
     */
    void goToGMill();
};

#endif // GERMANYMALT_H
