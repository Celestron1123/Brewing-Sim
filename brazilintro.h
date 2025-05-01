#ifndef BRAZILINTRO_H
#define BRAZILINTRO_H

/**
 * Intro window for Brazil.
 *
 * @authors Julia Maia
 * @date 04/24/2025
 *
 * Checked by Julia Maia
 */


#include <QWidget>

namespace Ui {
class BrazilIntro;
}

class BrazilIntro : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief BrazilIntro constructor
     * @param parent
     */
    explicit BrazilIntro(QWidget *parent = nullptr);

    /**
     * BrazilIntro destructor
     */
    ~BrazilIntro();

private slots:
    /**
     * @brief on_start_clicked - Goes to the next window and starts the brewing process
     */
    void on_start_clicked();

signals:
    /**
     * @brief goToHarvest - emits a signal to go to the harvest window
     */
    void goToHarvest();

private:
    Ui::BrazilIntro *ui;
};

#endif // BRAZILINTRO_H
