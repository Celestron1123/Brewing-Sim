#ifndef BRAZILHARVEST_H
#define BRAZILHARVEST_H

/**
 * Main brewing class for Brazil.
 *
 * @authors Steven Luo, Julia Maia, Elijah Potter
 * @date 04/24/2025
 *
 * Checked by Julia Maia
 */


#include <QWidget>

namespace Ui {
class brazilHarvest;
}

class brazilHarvest : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief brazilHarvest contructor
     * @param parent
     */
    explicit brazilHarvest(QWidget *parent = nullptr);

    /**
     * Destructor for brazilHarvest
     */
    ~brazilHarvest();

signals:

    /**
     * @brief goToBoiling - emits a signal to do to the next window
     */
    void goToBoiling();

private slots:

    /**
     * @brief on_harvestButton_clicked - "cuts" the sugarcane when clicked
     */
    void on_harvestButton_clicked();

    /**
     * @brief on_harvestButton_clicked - "cuts" sugarcane2 when clicked
     */
    void on_harvestButton2_clicked();

    /**
     * @brief on_harvestButton3_clicked - "cuts" sugarcane3 when clicked
     */
    void on_harvestButton3_clicked();

    /**
     * @brief on_continueButton_clicked - goes to the next window when clicked
     */
    void on_continueButton_clicked();

private:
    Ui::brazilHarvest *ui;
};

#endif // BRAZILHARVEST_H
