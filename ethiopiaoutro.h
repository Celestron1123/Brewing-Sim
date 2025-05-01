// Author - William Ngo
// Date - 4/19/25
// Header class for the outro of the ethiopia world.
#ifndef ETHIOPIAOUTRO_H
#define ETHIOPIAOUTRO_H

#include <QWidget>
#include <QPixmap>
#include <QRect>
#include <QResizeEvent>

namespace Ui {
class ethiopiaoutro;
}

class ethiopiaoutro : public QWidget
{
    Q_OBJECT

public:
    // Constructor: initializes the outro screen with optional parent
    explicit ethiopiaoutro(QWidget *parent = nullptr);

    // Destructor: cleans up dynamically allocated resources
    ~ethiopiaoutro();

signals:
    // Emitted when the player clicks to return to the main menu
    void goToMain();

protected:
    // Paints the background and UI elements (claypot, glasses, table, etc.)
    void paintEvent(QPaintEvent *event) override;

    // Handles mouse clicks — e.g., to simulate pouring Tej or advancing the screen
    void mousePressEvent(QMouseEvent *event) override;

    // Recalculates positions of UI elements when the window is resized
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::ethiopiaoutro *ui;     // Pointer to UI components generated from the .ui file

    // Images used in the outro screen
    QPixmap background;        // Background image (e.g., celebration scene)
    QPixmap claypotImg;        // Image of the claypot
    QPixmap glassImg;          // Image of an empty glass
    QPixmap glassFullImg;      // Image of a filled glass
    QPixmap tableImg;          // Image of the table surface

    // Geometry data for positioning the claypot and glasses
    QRect claypotRect;               // Area where the claypot is displayed
    QVector<QRect> glassRects;       // Areas where glasses are shown

    int filledCount = 0;      // Number of glasses that are currently shown as filled

    // Adjusts the position and layout of all elements based on window size
    void updateLayout();
};

#endif // ETHIOPIAOUTRO_H
