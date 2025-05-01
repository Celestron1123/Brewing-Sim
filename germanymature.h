#ifndef GERMANYMATURE_H
#define GERMANYMATURE_H

/**
 * The Maturing screen for the Germany Experience. Contains signals and slots for moving through other windows
 *
 * @author Ryan Hamerman
 * @date 04/24/25
 */

#include <QWidget>

namespace Ui {
class GermanyMature;
}

/**
 * @brief Class representing the Maturing screen for the Germany experience
 */
class GermanyMature : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the GermanyMature with a given model
     *
     * @param parent Pointer to the parent window
     */
    explicit GermanyMature(QWidget *parent = nullptr);

    /**
     * @brief Destructor for GermanyMature
     */
    ~GermanyMature();

private:
    /**
     * @brief Pointer to the UI object that holds the layout and widgets of GermanyMature
     */
    Ui::GermanyMature *ui;

private slots:
    /**
     * @brief Recives signal that the continue button has been pressed, sending a signal to MainWindow to move to the next scene
     */
    void on_continueButton_clicked();

signals:
    /**
     * @brief Signal sent to MainWindow to move to next scene
     */
    void goToGBottle();
};

#endif // GERMANYMATURE_H
