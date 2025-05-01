//Autor - William Ngo
//Date - 4/24/2025
// Header class for the physics/brew window the ethiopia world.
#ifndef ETHIOPIAPHYSICS_H
#define ETHIOPIAPHYSICS_H

#include <QWidget>
#include <Box2D/Box2D.h>
#include <QTimer>
#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>
#include <QElapsedTimer>
#include <QTimer>
#include <QLabel>

namespace Ui {
class ethiopiaphysics;
}

class ethiopiaphysics : public QWidget
{
    Q_OBJECT

public:
    // Constructor to initialize the widget and physics world
    explicit ethiopiaphysics(QWidget *parent = nullptr);

    // Destructor to clean up resources and Box2D world
    ~ethiopiaphysics();

public slots:
    // Begins the physics simulation
    void startPhysics();

    // Updates the physics world and triggers a repaint
    void updateTime();

    // Converts a QPoint (screen space) to Box2D world coordinates
    b2Vec2 screenToWorld(const QPoint &point);

    // Mouse interaction handlers for grabbing/moving Box2D bodies
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    // Handles rendering of the scene (called automatically on repaint)
    void paintEvent(QPaintEvent *event);

    // Shortcut development/testing button click (optional)
    void on_shortcutButton_clicked();

signals:
    // Signal to trigger transition to brewing stage
    void goToBrew();

    // Signal to trigger transition to the outro screen
    void goToOutro();

private slots:
    // Connected to the "Next" button to skip to the outro after brewing is done
    void on_nextButton_clicked();

private:
    Ui::ethiopiaphysics *ui;       // UI elements from the .ui file

    b2World world;                 // Box2D physics world
    QTimer timer;                  // Timer for world step updates

    // Physics bodies for the three main ingredients
    std::vector<b2Body*> gesho;
    std::vector<b2Body*> yeast;
    std::vector<b2Body*> honey;

    b2MouseJoint* mouseJoint = nullptr; // Used for dragging physics objects
    b2Body* groundBody = nullptr;       // Static ground for joints

    QTimer calendarTimer;               // Timer for simulated fermentation countdown

    // UI visuals and sprites
    QPixmap table;
    QPixmap bowl;
    QPixmap claypot;
    QPixmap background;
    QPixmap claypotfront;
    QPixmap lid;
    QPixmap calendarImage;
    QPixmap xMark;

    QString explanationText;            // Instructions or narration overlay

    // Flags for interaction state
    bool showCalendar = false;          // Whether to show the 3-day calendar
    int xDaysMarked = 0;                // Tracks how many "days" have passed
    bool lidON = false;                 // Whether the lid has been placed on the pot
    bool waitFinished = false;          // Whether the fermentation wait has completed
    bool waitingInProgress = false;     // Whether the wait timer is running

    // Checks if all required ingredients are inside the pot
    bool ingredientsInPot() const;
};

#endif // ETHIOPIAPHYSICS_H
