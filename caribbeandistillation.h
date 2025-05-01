#ifndef CARIBBEANDISTILLATION_H
#define CARIBBEANDISTILLATION_H

/**
 * @brief The Distillation screen for the Caribbean section of the app. Simulates the distillation of fermented liquid.
 *
 * @author Steven Luo
 * @date 04/24/25
 */

#include <QWidget>
#include <QTimer>

namespace Ui {
class CaribbeanDistillation;
}

/**
 * @brief Class representing the Distillation screen for the Caribbean section of the app
 */
class CaribbeanDistillation : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the CaribbeanDistillation window.
     * @param parent Pointer to parent widget
     */
    explicit CaribbeanDistillation(QWidget *parent = nullptr);

    /**
     * @brief Destructor for CaribbeanDistillation
     */
    ~CaribbeanDistillation();

signals:
    /**
     * @brief Signal to transition to the CaribbeanMaturation screen
     */
    void goToMaturation();

public slots:
    /**
     * @brief Renders the current screen
     */
    void paintEvent(QPaintEvent *);

private slots:
    /**
     * @brief Handles click on the distill button to begin distillation process
     */
    void on_distillButton_clicked();

    /**
     * @brief Handles click on the continue button to proceed to maturation
     */
    void on_continueButton_clicked();

private:
    /**
     * @brief Pointer to the UI object that holds the layout and widgets of CaribbeanDistillation
     */
    Ui::CaribbeanDistillation *ui;

    /**
     * @brief Background image used in the distillation screen
     */
    QPixmap background;

    /**
     * @brief Image of the pot still used for distillation
     */
    QPixmap potStill;

    /**
     * @brief Timer for the distillation countdown
     */
    QTimer distillCountdownTimer;

    /**
     * @brief Countdown value while distilling
     */
    int distillCountdownValue;
};

#endif // CARIBBEANDISTILLATION_H
