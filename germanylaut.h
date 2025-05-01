#ifndef GERMANYLAUT_H
#define GERMANYLAUT_H

/**
 * The Lautering screen for the Germany Experience. Contains signals and slots for moving through other windows
 *
 * @author Ryan Hamerman
 * @date 04/24/25
 */

#include <QWidget>

namespace Ui {
class GermanyLaut;
}

/**
 * @brief Class representing the Lautering screen for the Germany experience
 */
class GermanyLaut : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the GermanyLaut with a given model
     *
     * @param parent Pointer to the parent window
     */
    explicit GermanyLaut(QWidget *parent = nullptr);

    /**
     * @brief Destructor for GermanyLaut
     */
    ~GermanyLaut();

private:
    /**
     * @brief Pointer to the UI object that holds the layout and widgets of GermanyLaut
     */
    Ui::GermanyLaut *ui;

private slots:
    /**
     * @brief Recives signal that the continue button has been pressed, sending a signal to MainWindow to move to the next scene
     */
    void on_continueButton_clicked();

signals:
    /**
     * @brief Signal sent to MainWindow to move to next scene
     */
    void goToGHop();
};

#endif // GERMANYLAUT_H
