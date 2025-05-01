#ifndef CARIBBEANFERMENTATION_H
#define CARIBBEANFERMENTATION_H

/**
 * @brief The Fermentation screen for the Caribbean section of the app. Simulates yeast-molasses interaction.
 *
 * @author Steven Luo
 * @date 04/24/25
 */

#include <QWidget>
#include <Box2D/Box2D.h>
#include <QTimer>

namespace Ui {
class CaribbeanFermentation;
}

/**
 * @brief Class representing the Fermentation screen for the Caribbean section of the app
 */
class CaribbeanFermentation : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the CaribbeanFermentation window.
     * @param parent Pointer to parent widget
     */
    explicit CaribbeanFermentation(QWidget *parent = nullptr);

    /**
     * @brief Destructor for CaribbeanFermentation
     */
    ~CaribbeanFermentation();

signals:
    /**
     * @brief Signal to transition to the CaribbeanDistillation screen
     */
    void goToDistillation();

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
     * @brief Handles click on the pour button to pour molasses
     */
    void on_pourButton_clicked();

    /**
     * @brief Handles click to begin the fermentation countdown
     */
    void on_beginFermentationButton_clicked();

    /**
     * @brief Handles click on continue to proceed to distillation
     */
    void on_continueButton_clicked();

private:
    /**
     * @brief Pointer to the UI object that holds the layout and widgets of CaribbeanFermentation
     */
    Ui::CaribbeanFermentation *ui;

    /**
     * @brief Physics world used by Box2D
     */
    b2World world;

    /**
     * @brief Timer for controlling physics and rendering updates
     */
    QTimer timer;

    /**
     * @brief Static ground body used by Box2D
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
     * @brief Table image used in the fermentation scene
     */
    QPixmap table;

    /**
     * @brief Image of the fermentation barrel
     */
    QPixmap barrel;

    /**
     * @brief Front overlay image of the fermentation barrel
     */
    QPixmap barrelFront;

    /**
     * @brief Image of the molasses bowl
     */
    QPixmap bowl;

    /**
     * @brief Hanging molasses barrel used for pouring
     */
    QPixmap molassesBarrelHanging;

    /**
     * @brief Visual stream showing molasses being poured
     */
    QPixmap molassesPourStream;

    /**
     * @brief Vector of yeast physics bodies
     */
    std::vector<b2Body*> yeast;

    /**
     * @brief Whether molasses is actively pouring
     */
    bool isPouring = false;

    /**
     * @brief Whether pouring is finished
     */
    bool isPoured = false;

    /**
     * @brief Event filter for input during the scene
     */
    bool eventFilter(QObject *object, QEvent *event);

    /**
     * @brief Timer for countdown during pouring
     */
    QTimer pourCountdownTimer;

    /**
     * @brief Countdown value while pouring molasses
     */
    int pourCountdownValue;

    /**
     * @brief Timer for countdown during fermentation
     */
    QTimer fermentationCountdownTimer;

    /**
     * @brief Countdown value while fermenting
     */
    int fermentationCountdownValue;

    /**
     * @brief Checks if yeast has been added to the fermentation barrel
     * @return true if yeast is present, false otherwise
     */
    bool isYeastInFermentationBarrel() const;
};

#endif // CARIBBEANFERMENTATION_H
