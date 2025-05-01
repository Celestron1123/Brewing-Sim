#ifndef GERMANYBOTTLE_H
#define GERMANYBOTTLE_H

/**
 * The Bottling screen for the Germany Experience. Contains signals and slots for moving through other windows
 *
 * @author Ryan Hamerman
 * @date 04/24/25
 */

#include <QWidget>

namespace Ui {
class GermanyBottle;
}

/**
 * @brief Class representing the Bottling screen for the Germany experience
 */
class GermanyBottle : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the GermanyBottle with a given model
     *
     * @param parent Pointer to the parent window
     */
    explicit GermanyBottle(QWidget *parent = nullptr);

    /**
     * @brief Destructor for GermanyBottle
     */
    ~GermanyBottle();

private:
    /**
     * @brief Pointer to the UI object that holds the layout and widgets of GermanyBottle
     */
    Ui::GermanyBottle *ui;

private slots:
    /**
     * @brief Recives signal that the continue button has been pressed, sending a signal to MainWindow to move to the map screen
     */
    void on_continueButton_clicked();

signals:
    /**
     * @brief Signal sent to MainWindow to move to the map screen
     */
    void goToMain();
};

#endif // GERMANYBOTTLE_H
