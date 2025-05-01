#ifndef GERMANYMILL_H
#define GERMANYMILL_H

/**
 * The Milling screen for the Germany Experience. Contains signals and slots for moving through other windows
 *
 * @author Ryan Hamerman
 * @date 04/24/25
 */

#include <QWidget>

namespace Ui {
class GermanyMill;
}

/**
 * @brief Class representing the Milling screen for the Germany experience
 */
class GermanyMill : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the GermanyMill with a given model
     *
     * @param parent Pointer to the parent window
     */
    explicit GermanyMill(QWidget *parent = nullptr);

    /**
     * @brief Destructor for GermanyMill
     */
    ~GermanyMill();

private:
    /**
     * @brief Pointer to the UI object that holds the layout and widgets of GermanyMill
     */
    Ui::GermanyMill *ui;

private slots:
    /**
     * @brief Recives signal that the continue button has been pressed, sending a signal to MainWindow to move to the next scene
     */
    void on_continueButton_clicked();

signals:
    /**
     * @brief Signal sent to MainWindow to move to next scene
     */
    void goToGMash();
};

#endif // GERMANYMILL_H
