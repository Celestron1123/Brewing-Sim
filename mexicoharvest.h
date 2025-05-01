#ifndef MEXICOHARVEST_H
#define MEXICOHARVEST_H
/**
 * @class MexicoHarvest
 * @brief Mexico widget in which the user can simulate "picking" the agave plants.
 *
 *@authors Ryan Hamerman, Steven Luo, Julia Maia, Yudith Mendoza, William Ngo, Elijah Potter
 */

#include <QWidget>

namespace Ui {
class MexicoHarvest;
}

class MexicoHarvest : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     */
    explicit MexicoHarvest(QWidget *parent = nullptr);
    /**
     * @brief Destructor
     */
    ~MexicoHarvest();

private:
    Ui::MexicoHarvest *ui;
    bool agave1Clicked = false;
    bool agave2Clicked = false;
    bool agave3Clicked = false;

private slots:
    /**
     * @brief Slot triggered when first plant is clicked.
     * Updates corresponding UI element.
     */
    void onAgaveOneClicked();
    /**
     * @brief Slot triggered when second plant is clicked
     * Updates corresponding UI element.
     */
    void onAgaveTwoClicked();
    /**
     * @brief Slot triggered when third plant is clicked
     * Updates corresponding UI element.
     */
    void onAgaveThreeClicked();
    /**
     * @brief Handles when user clicks continue buttons.
     * Emits signal for next widget.
     */
    void onContinueClicked();
    /**
     * @brief Checks if all three plants have been clicked.
     * Enables continue button if so.
     */
    void checkAllAgavesClicked();

signals:
    /**
     * @brief Calls for next widget.
     */
    void goToCook();
};

#endif // MEXICOHARVEST_H
