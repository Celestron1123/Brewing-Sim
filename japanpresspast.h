#ifndef JAPANPRESSPAST_H
#define JAPANPRESSPAST_H

/**
 * Main Japan pressing window
 *
 * @author Elijah Potter
 * @date 4/24/25
 */

#include <QWidget>

namespace Ui {
class JapanPressPast;
}

/**
 * @brief The JapanPressPast class
 */
class JapanPressPast : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief JapanPressPast constructor
     * @param parent
     */
    explicit JapanPressPast(QWidget *parent = nullptr);

    /**
    * @brief The JapanPressPast destructor
    */
    ~JapanPressPast();

private:
    /**
     * @brief ui pointer
     */
    Ui::JapanPressPast *ui;

    /**
     * @brief Checks whether or not the button has been pressed
     */
    bool buttonPressed;

signals:
    /**
     * @brief Signals to go to the next screen
     */
    void goToOutro();

private slots:
    /**
     * @brief Changes the position of the arm
     * @param value height of the arm
     */
    void adjustPosition(int value);

    /**
     * @brief Handles the firing button
     */
    void on_pasteruizer_clicked();

    /**
     * @brief Handles the next button
     */
    void on_pushButton_clicked();
};

#endif // JAPANPRESSPAST_H
