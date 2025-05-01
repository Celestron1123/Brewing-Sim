#ifndef GERMANYMASH_H
#define GERMANYMASH_H

/**
 * The Mashing screen for the Germany Experience. Contains signals and slots for moving through other windows
 *
 * @author Ryan Hamerman
 * @date 04/24/25
 */

#include <QWidget>

namespace Ui {
class GermanyMash;
}

/**
 * @brief Class representing the Mashing screen for the Germany experience
 */
class GermanyMash : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the GermanyMash with a given model
     *
     * @param parent Pointer to the parent window
     */
    explicit GermanyMash(QWidget *parent = nullptr);

    /**
     * @brief Destructor for GermanyMash
     */
    ~GermanyMash();

private:
    /**
     * @brief Pointer to the UI object that holds the layout and widgets of GermanyMash
     */
    Ui::GermanyMash *ui;

private slots:
    /**
     * @brief Recives signal that the continue button has been pressed, sending a signal to MainWindow to move to the next scene
     */
    void on_continueButton_clicked();

signals:
    /**
     * @brief Signal sent to MainWindow to move to next scene
     */
    void goToGLaut();
};

#endif // GERMANYMASH_H
