#ifndef BRAZILPRESSPAST_H
#define BRAZILPRESSPAST_H

/**
 * Distillation window for Brazil.
 *
 * @authors Julia Maia
 * @date 04/24/2025
 *
 * Checked by Julia Maia
 */

#include <QWidget>

namespace Ui {
class BrazilPressPast;
}

class BrazilPressPast : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief BrazilPressPast constructor
     * @param parent
     */
    explicit BrazilPressPast(QWidget *parent = nullptr);

    /**
     * BrazilPressPast destructor
     */
    ~BrazilPressPast();

signals:

    /**
     * @brief goToOutro - Emits a signal to go to the outro window
     */
    void goToOutro();

private slots:
    /**
     * @brief on_heat_clicked - Displays fire and steam in the window once clicked.
     */
    void on_heat_clicked();

    /**
     * @brief on_continueButton_clicked - Goes to the outro window once clicked
     */
    void on_continueButton_clicked();

private:
    Ui::BrazilPressPast *ui;
};

#endif // BRAZILPRESSPAST_H
