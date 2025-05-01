#ifndef CREDITSWINDOW_H
#define CREDITSWINDOW_H

/**
 * @brief The Credits screen for the app. Displays acknowledgements and contributors.
 *
 * @author Steven Luo
 * @date 04/24/25
 */

#include <QWidget>

namespace Ui {
class CreditsWindow;
}

/**
 * @brief Class representing the Credits screen of the app
 */
class CreditsWindow : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the CreditsWindow.
     * @param parent Pointer to parent widget
     */
    explicit CreditsWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor for CreditsWindow
     */
    ~CreditsWindow();

signals:
    /**
     * @brief Signal to return to the start or main screen
     */
    void goToStart();

private slots:
    /**
     * @brief Handles click on the back button to return to the start screen
     */
    void on_backButton_clicked();

private:
    /**
     * @brief Pointer to the UI object that holds the layout and widgets of CreditsWindow
     */
    Ui::CreditsWindow *ui;
};

#endif // CREDITSWINDOW_H
