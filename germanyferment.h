#ifndef GERMANYFERMENT_H
#define GERMANYFERMENT_H

/**
 * The Fermenting screen for the Germany Experience. Contains signals and slots for moving through other windows
 *
 * @author Ryan Hamerman
 * @date 04/24/25
 */

#include <QWidget>

namespace Ui {
class GermanyFerment;
}

/**
 * @brief Class representing the Fermenting screen for the Germany experience
 */
class GermanyFerment : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the GermanyFerment with a given model
     *
     * @param parent Pointer to the parent window
     */
    explicit GermanyFerment(QWidget *parent = nullptr);

    /**
     * @brief Destructor for GermanyFerment
     */
    ~GermanyFerment();

private:
    /**
     * @brief Pointer to the UI object that holds the layout and widgets of GermanyFerment
     */
    Ui::GermanyFerment *ui;

private slots:
    /**
     * @brief Recives signal that the continue button has been pressed, sending a signal to MainWindow to move to the next scene
     */
    void on_continueButton_clicked();

signals:
    /**
     * @brief Signal sent to MainWindow to move to next scene
     */
    void goToGMat();
};

#endif // GERMANYFERMENT_H
