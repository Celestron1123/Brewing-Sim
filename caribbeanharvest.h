#ifndef CARIBBEANHARVEST_H
#define CARIBBEANHARVEST_H

/**
 * @brief The Harvest screen for the Caribbean section of the app.
 *
 * @author Steven Luo
 * @date 04/24/25
 */

#include <QWidget>

namespace Ui {
class CaribbeanHarvest;
}

/**
 * @brief Class representing the Harvest screen for the Caribbean section of the app
 */
class CaribbeanHarvest : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the CaribbeanHarvest window.
     * @param parent Pointer to parent widget
     */
    explicit CaribbeanHarvest(QWidget *parent = nullptr);

    /**
     * @brief Destructor for CaribbeanHarvest
     */
    ~CaribbeanHarvest();

signals:
    /**
     * @brief Signal to transition to the CaribbeanBoiling screen
     */
    void goToBoiling();

private slots:
    /**
     * @brief Handles click on the first sugarcane button
     */
    void on_harvestButton_clicked();

    /**
     * @brief Handles click on the second sugarcane button
     */
    void on_harvestButton_2_clicked();

    /**
     * @brief Handles click on the third sugarcane button
     */
    void on_harvestButton_3_clicked();

    /**
     * @brief Handles click on the continue button to go to boiling screen
     */
    void on_continueButton_clicked();

private:
    /**
     * @brief Pointer to the UI object that holds the layout and widgets of CaribbeanHarvest
     */
    Ui::CaribbeanHarvest *ui;
};

#endif // CARIBBEANHARVEST_H
