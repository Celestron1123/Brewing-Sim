#ifndef MEXICO_H
#define MEXICO_H

/**
 * @class Mexico
 * @brief Mexico widget in which the user can interact the physically simulated ingredients
 *
 * @authors Ryan Hamerman, Steven Luo, Julia Maia, Yudith Mendoza, William Ngo, Elijah Potter
 */

#include <QWidget>
#include <Box2D/Box2D.h>
#include <QTimer>
#include <QMouseEvent>
#include <QPainter>

namespace Ui {
class Mexico;
}

class Mexico : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     */
    explicit Mexico(QWidget *parent = nullptr);
    /**
     * @brief Destructor.
     */
    ~Mexico();

private:
    Ui::Mexico *ui;
    b2World world;
    QTimer timer;
    std::vector<b2Body*> yeast;
    QPixmap background;
    b2Body* groundBody;
    QPixmap table;
    QPixmap bucket;
    QPixmap bucketFront;
    QPixmap bowl;
    b2MouseJoint* mouseJoint = nullptr;
    /**
     * @brief Checks if all yeast cells are in bucket.
     * @return True if yeast are all within bucket, false otherwise.
     */
    bool ingredientsInPot() const;

public slots:
    /**
     * @brief Starts physics simuluation by starting the update timer.
     */
    void startPhysics();
    /**
     * @brief Helps convert screen Qt coordinates to Box2D world coordinates
     * @param QT point
     * @return Corresponding Box2D world coordinate
     */
    b2Vec2 screenToWorld(const QPoint &point);
    /**
     * @brief Handles mouse move events.
     * Used to detect if a yeast particle was clicked and attatch a mouse joint to it.
     * @param The mouse press event.
     */
    void mousePressEvent(QMouseEvent *event);
    /**
     * @brief Handles mouse move events.
     * Updates position of joint if one is active.
     * @param The mouse move event.
     */
    void mouseMoveEvent(QMouseEvent *event);
    /**
     * @brief Handles mouse release events.
     * Destroys active mouse joint if one exists.
     * @param The mouse release event.
     */
    void mouseReleaseEvent(QMouseEvent *event);
    /**
     * @brief Paint event to create scenery and visual elements.
     * @param The paint event.
     */
    void paintEvent(QPaintEvent *event);
    /**
     * @brief Updates Box2D world and triggers a repaint.
     */
    void updateTime();

private slots:
    /**
     * @brief Handles when continue button is clicked from UI.
     * Stops physics timer and emits signal to continue to the next widget.
     * @param
     */
    void onContinueClicked();
    /**
     * @brief Moves all yeast cells over pot.
     * Called when user clicks "auto mix" button.
     * @param
     */
    void onAutoMixclicked();

signals:
    /**
     * @brief Calls for next widget.
     */
    void goToOutro();
};

#endif // MEXICO_H
