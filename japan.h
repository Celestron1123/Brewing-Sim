#ifndef JAPAN_H
#define JAPAN_H

/**
 * Main Japan physics window
 *
 * @author Elijah Potter
 * @date 4/24/25
 */

#include <QWidget>
#include <Box2D/Box2D.h>
#include <QTimer>
#include <QMouseEvent>
#include <QPainter>

namespace Ui {
class Japan;
}

/**
 * @brief The Japan class
 */
class Japan : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs Japan window
     * @param parent Pointer to parent window
     */
    explicit Japan(QWidget *parent = nullptr);

    /**
     * @brief Japan destructor
     */
    ~Japan();

private:
    /**
     * @brief Japan's ui pointer
     */
    Ui::Japan *ui;

    /**
     * @brief Physics simulation foundation
     */
    b2World world;

    /**
     * @brief Physics timer
     */
    QTimer timer;

    /**
     * @brief Vector containing simulated rice bodies
     */
    std::vector<b2Body*> rice;

    /**
     * @brief Vector containing simulated yeast bodies
     */
    std::vector<b2Body*> yeast;

    /**
     * @brief Vector containing simulated koji bodies
     */
    std::vector<b2Body*> koji;

    /**
     * @brief Joint joining physics bodies and mouse
     */
    b2MouseJoint* mouseJoint = nullptr;

    /**
     * @brief Static ground body
     */
    b2Body* groundBody;

    /**
     * @brief background image
     */
    QPixmap background;

    /**
     * @brief table image
     */
    QPixmap table;

    /**
     * @brief kojiBowl image
     */
    QPixmap kojiBowl;

    /**
     * @brief cauldron image
     */
    QPixmap cauldron;

    /**
     * @brief cauldronFront image
     */
    QPixmap cauldronFront;

    /**
     * @brief Check for if the ingredients are in the pot
     * @return bool
     */
    bool ingredientsInPot() const;

public slots:
    /**
     * @brief Is run at 60FPS to simulate movement
     */
    void updateTime();

    /**
     * @brief Helper to convert Qt widget coordinates to Box2D world coordinates
     * @param Point on the screen
     * @return b2 vector
     */
    b2Vec2 screenToWorld(const QPoint &point);

    /**
     * @brief Handles the press of a mouse
     * @param event
     */
    void mousePressEvent(QMouseEvent *event);

    /**
     * @brief Handles the movement of a mouse
     * @param event
     */
    void mouseMoveEvent(QMouseEvent *event);

    /**
     * @brief Handles the release of a mouse
     * @param event
     */
    void mouseReleaseEvent(QMouseEvent *event);

    /**
     * @brief Run when all the objects need to be painted on the screen
     * @param event
     */
    void paintEvent(QPaintEvent *event);

    /**
     * @brief Starts the physics sim
     */
    void startPhysics();

signals:
    /**
     * @brief Goes to the next screen
     */
    void goToPress();

private slots:
    /**
     * @brief Handles going to the next screen
     */
    void on_pushButton_clicked();

    /**
     * @brief Handles skipping the drag
     */
    void on_dragSkip_clicked();
};

#endif // JAPAN_H
