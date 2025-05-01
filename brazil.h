#ifndef BRAZIL_H
#define BRAZIL_H

/**
 * Main brewing class for Brazil.
 *
 * @authors Steven Luo, Julia Maia, Elijah Potter
 * @date 04/24/2025
 *
 * Checked by Julia Maia
 */

#include <QWidget>
#include <Box2D/Box2D.h>
#include <QTimer>
#include <QMouseEvent>
#include <QPainter>

namespace Ui {
class Brazil;
}

class Brazil : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Brazil constructor
     * @param parent
     */
    explicit Brazil(QWidget *parent = nullptr);

    /**
     * Brazil destructor
     **/
    ~Brazil();

private:
    Ui::Brazil *ui;
    b2World world;
    QTimer timer;
    b2Body* sugarcaneJuice = nullptr;
    std::vector<b2Body*> yeast;
    b2MouseJoint* mouseJoint = nullptr;
    b2Body* groundBody;
    QPixmap background;
    QPixmap table;
    QPixmap sugarcaneBowl;
    QPixmap cauldron;
    QPixmap cauldronFront;
    QPixmap juiceImage;
    bool ingredientsInPot() const;

public slots:

    /**
     * @brief updateTime updates time for the class
     */
    void updateTime();

    /**
     * @brief screenToWorld box2D objects
     * @param point
     */
    b2Vec2 screenToWorld(const QPoint &point);

    /**
     * @brief mousePressEvent tracks mouse presses
     * @param event
     */
    void mousePressEvent(QMouseEvent *event);

    /**
     * @brief mouseMoveEvent tracks mouse movements
     * @param event
     */
    void mouseMoveEvent(QMouseEvent *event);

    /**
     * @brief mouseReleaseEvent tracks mouse release
     * @param event
     */
    void mouseReleaseEvent(QMouseEvent *event);

    /**
     * @brief paintEvent draws all objects in the window.
     * @param event
     */
    void paintEvent(QPaintEvent *event);

    /**
     * @brief startPhysics starts the box2d physics for the window
     */
    void startPhysics();

signals:

    /**
     * @brief goToPress emits a signal to go to the next window.
     */
    void goToPress();

private slots:
    /**
     * @brief on_continueButton_clicked continues to the next window once continueButton is clicked.
     */
    void on_continueButton_clicked();

    /**
     * @brief on_dragSkip_clicked auto mixes the ingredients once clicked.
     */
    void on_dragSkip_clicked();
};

#endif // BRAZIL_H
