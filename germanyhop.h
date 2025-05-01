#ifndef GERMANYHOP_H
#define GERMANYHOP_H

/**
 * The Hopping screen for the Germany Experience. Contains signals and slots for moving through other windows. Also implements Box2D for physics
 * simulations for moving hops into the pot.
 *
 * @author Ryan Hamerman
 * @cite Elijah Potter
 * @date 04/24/25
 */

#include <QWidget>
#include <Box2D/Box2D.h>
#include <QTimer>
#include <QMouseEvent>
#include <QPainter>

namespace Ui {
class GermanyHop;
}

/**
 * @brief Class representing the Hopping screen for the Germany experience
 */
class GermanyHop : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the GermanyHop with a given model
     *
     * @param parent Pointer to the parent window
     */
    explicit GermanyHop(QWidget *parent = nullptr);

    /**
     * @brief Destructor for GermanyHop
     */
    ~GermanyHop();

private:
    /**
     * @brief Pointer to the UI object that holds the layout and widgets of GermanyHop
     */
    Ui::GermanyHop *ui;

    /**
     * @brief Holds the world information such as gravity
     */
    b2World world;

    /**
     * @brief Holds the timer used for physics/frame updating
     */
    QTimer timer;

    /**
     * @brief Vector containing the hops physics bodys in the scene
     */
    std::vector<b2Body*> hops;

    /**
     * @brief Joint that connects a physics body to the user's mouse
     */
    b2MouseJoint* mouseJoint = nullptr;

    /**
     * @brief Global holder for wallBody's properties
     */
    b2Body* groundBody;

    /**
     * @brief Holds the background image
     */
    QPixmap background;

    /**
     * @brief Holds the table image
     */
    QPixmap table;

    /**
     * @brief Holds the bowl image
     */
    QPixmap kojiBowl;

    /**
     * @brief Holds the cauldron image
     */
    QPixmap cauldron;

    /**
     * @brief Holds the cauldronFront image
     */
    QPixmap cauldronFront;

    /**
     * @brief Holds the hop image
     */
    QPixmap hop;

    /**
     * @brief Function that determines if all of the hops physics bodys are "inside" the pot
     * @returns True if all inside, false otherwise
     */
    bool hopsInPot() const;

public slots:
    /**
     * @brief Function called when the timer goes off. Updates the physics and repaints the scene
     */
    void updateTime();

    /**
     * @brief Helper to convert Qt widget coordinates to Box2D world coordinates
     * @param point The Qt point
     * @returns the Box2D point
     */
    b2Vec2 screenToWorld(const QPoint &point);

    /**
     * @brief Handles the event when the mouse is clicked
     * @param event The mouse event
     */
    void mousePressEvent(QMouseEvent *event);

    /**
     * @brief Handles the event when the mouse is moved
     * @param event The mouse event
     */
    void mouseMoveEvent(QMouseEvent *event);

    /**
     * @brief Handles the event when the mouse is released
     * @param event Unused param
     */
    void mouseReleaseEvent(QMouseEvent *event);

    /**
     * @brief Draws all the visuals on the screen including the physics bodys and all images
     * @param event Unused param
     */
    void paintEvent(QPaintEvent *event);

    /**
     * @brief Starts the timer object
     */
    void startPhysics();

signals:
    /**
     * @brief Signal sent to MainWindow to move to next scene
     */
    void goToGFerment();

    /**
     * @brief Signal sent to the continue button when all the hops are in the pot
     */
    void allInPot();

private slots:
    /**
     * @brief Recives signal that the continue button has been pressed, sending a signal to MainWindow to move to the next scene
     */
    void on_continueButton_clicked();
};

#endif // GERMANYHOP_H
