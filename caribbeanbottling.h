#ifndef CARIBBEANBOTTLING_H
#define CARIBBEANBOTTLING_H

/**
 * @brief The Bottling screen for the Caribbean section of the app. Finalizes the process by bottling the aged rum.
 *
 * @author Steven Luo
 * @date 04/24/25
 */

#include <QWidget>

namespace Ui {
class CaribbeanBottling;
}

/**
 * @brief Class representing the Bottling screen for the Caribbean section of the app
 */
class CaribbeanBottling : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the CaribbeanBottling window.
     * @param parent Pointer to parent widget
     */
    explicit CaribbeanBottling(QWidget *parent = nullptr);

    /**
     * @brief Destructor for CaribbeanBottling
     */
    ~CaribbeanBottling();

signals:
    /**
     * @brief Signal to return to the main screen or map
     */
    void goToMain();

public slots:
    /**
     * @brief Renders the current screen
     */
    void paintEvent(QPaintEvent *);

private slots:
    /**
     * @brief Handles click on the bottle button to finish the bottling process
     */
    void on_bottleButton_clicked();

    /**
     * @brief Handles click to go back to the main map or menu
     */
    void on_backToMapButton_clicked();

private:
    /**
     * @brief Pointer to the UI object that holds the layout and widgets of CaribbeanBottling
     */
    Ui::CaribbeanBottling *ui;

    /**
     * @brief Background image for the bottling scene
     */
    QPixmap background;

    /**
     * @brief Image of the bottle and table setup
     */
    QPixmap bottleAndTable;

    /**
     * @brief Banner indicating that rum is finished
     */
    QPixmap rumFinishedBanner;
};

#endif // CARIBBEANBOTTLING_H
