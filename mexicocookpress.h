#ifndef MEXICOCOOKPRESS_H
#define MEXICOCOOKPRESS_H
/**
 * @class MexicoCookPress
 * @brief Mexico widget in which the user can simulate cooking and pressing the agave plants
 *
 *@authors Ryan Hamerman, Steven Luo, Julia Maia, Yudith Mendoza, William Ngo, Elijah Potter
 */

#include <QWidget>

namespace Ui {
class MexicoCookPress;
}

class MexicoCookPress : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     */
    explicit MexicoCookPress(QWidget *parent = nullptr);
    /**
     * @brief Destructor.
     */
    ~MexicoCookPress();

private:
    Ui::MexicoCookPress *ui;
    bool ovenIsClosed = false;

private slots:
    /**
     * @brief Handles when steamer button is clicked.
     * Changes element to show a closed autoclave.
     * Also checks if user can continue to next widget.
     */
    void onSteamerClicked();
    /**
     * @brief Updates UI as user adjusts slider.
     * Changes element to show a press arm going up and down.
     * Also checks if user can continue to next widget.
     * @param The position of UI slider
     */
    void adjustPosition(int value);
    /**
     * @brief Handles when user clicks continue button.
     * Emits signal for next widget.
     */
    void onContinueClicked();

signals:
    /**
     * @brief Calls for next widget.
     */
    void goToMix();
};

#endif // MEXICOCOOKPRESS_H
