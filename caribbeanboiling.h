#ifndef CARIBBEANBOILING_H
#define CARIBBEANBOILING_H

/**
 * @brief The Boiling screen for the Caribbean section of the app. Simulates boiling sugarcane juice into molasses.
 *
 * @author Steven Luo
 * @cite Elijah Potter
 * @date 04/24/25
 */

#include <QWidget>
#include <Box2D/Box2D.h>
#include <QTimer>

namespace Ui {
class CaribbeanBoiling;
}

/**
 * @brief Class representing the Boiling screen for the Caribbean section of the app
 */
class CaribbeanBoiling : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the CaribbeanBoiling window.
     * @param parent Pointer to parent widget
     */
    explicit CaribbeanBoiling(QWidget *parent = nullptr);

    /**
     * @brief Destructor for CaribbeanBoiling
     */
    ~CaribbeanBoiling();

signals:
    /**
     * @brief Signal to transition to the CaribbeanFermentation screen
     */
    void goToFermentation();

public slots:
    /**
     * @brief Updates the simulation time for physics and rendering
     */
    void updateTime();

    /**
     * @brief Converts screen coordinates to Box2D world coordinates
     * @param point The QPoint on screen
     * @return Corresponding world coordinates as b2Vec2
     */
    b2Vec2 screenToWorld(const QPoint &point);

    /**
     * @brief Starts the physics simulation
     */
    void startPhysics();

    /**
     * @brief Renders the current screen
     */
    void paintEvent(QPaintEvent *);

    /**
     * @brief Handles mouse press events
     */
    void mousePressEvent(QMouseEvent *event);

    /**
     * @brief Handles mouse movement events
     */
    void mouseMoveEvent(QMouseEvent *event);

    /**
     * @brief Handles mouse release events
     */
    void mouseReleaseEvent(QMouseEvent *);

private slots:
    /**
     * @brief Handles click on the boil button
     */
    void on_boilButton_clicked();

    /**
     * @brief Handles click on the continue button to advance to fermentation
     */
    void on_continueButton_clicked();

private:
    /**
     * @brief Pointer to the UI object that holds the layout and widgets of CaribbeanBoiling
     */
    Ui::CaribbeanBoiling *ui;

    /**
     * @brief Physics world used by Box2D
     */
    b2World world;

    /**
     * @brief Timer for controlling physics and rendering updates
     */
    QTimer timer;

    /**
     * @brief Physics body representing sugarcane juice
     */
    b2Body* sugarCaneJuice = nullptr;

    /**
     * @brief Physics body representing molasses
     */
    b2Body* molasses = nullptr;

    /**
     * @brief Static ground body used by Box2D for anchoring objects
     */
    b2Body* groundBody = nullptr;

    /**
     * @brief Joint used to drag objects with the mouse
     */
    b2MouseJoint* mouseJoint = nullptr;

    /**
     * @brief Background image
     */
    QPixmap background;

    /**
     * @brief Table image in the boiling scene
     */
    QPixmap table;

    /**
     * @brief Pot image used for the back layer
     */
    QPixmap pot;

    /**
     * @brief Pot front overlay image
     */
    QPixmap potFront;

    /**
     * @brief Determines if juice is already in the pot
     * @return true if juice is in pot, false otherwise
     */
    bool isJuiceInPot() const;

    /**
     * @brief Creates molasses in the simulation
     */
    void createMolasses();

    /**
     * @brief Timer used to count down boiling duration
     */
    QTimer boilCountdownTimer;

    /**
     * @brief Value of the countdown during boiling
     */
    int countdownValue;
};

#endif // CARIBBEANBOILING_H
