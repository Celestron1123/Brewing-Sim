#ifndef CARIBBEANMATURATION_H
#define CARIBBEANMATURATION_H

/**
 * @brief The Maturation screen for the Caribbean section of the app. Simulates the aging process of the distilled rum.
 *
 * @author Steven Luo
 * @date 04/24/25
 */

#include <QWidget>
#include <QTimer>

namespace Ui {
class CaribbeanMaturation;
}

/**
 * @brief Class representing the Maturation screen for the Caribbean section of the app
 */
class CaribbeanMaturation : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the CaribbeanMaturation window.
     * @param parent Pointer to parent widget
     */
    explicit CaribbeanMaturation(QWidget *parent = nullptr);

    /**
     * @brief Destructor for CaribbeanMaturation
     */
    ~CaribbeanMaturation();

signals:
    /**
     * @brief Signal to transition to the CaribbeanBottling screen
     */
    void goToBottling();

public slots:
    /**
     * @brief Renders the current screen
     */
    void paintEvent(QPaintEvent *);

private slots:
    /**
     * @brief Handles click on the mature button to start the aging process
     */
    void on_matureButton_clicked();

    /**
     * @brief Handles click on the continue button to proceed to bottling
     */
    void on_continueButton_clicked();

private:
    /**
     * @brief Pointer to the UI object that holds the layout and widgets of CaribbeanMaturation
     */
    Ui::CaribbeanMaturation *ui;

    /**
     * @brief Background image for the maturation scene
     */
    QPixmap background;

    /**
     * @brief Image of barrels used to age the rum
     */
    QPixmap barrels;

    /**
     * @brief Banner image indicating aging is complete
     */
    QPixmap rumAgedBanner;

    /**
     * @brief Timer used for the aging countdown
     */
    QTimer matureCountdownTimer;

    /**
     * @brief Current countdown value for the aging process
     */
    int matureCountdownValue;
};

#endif // CARIBBEANMATURATION_H
