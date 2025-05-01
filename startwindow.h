#ifndef STARTWINDOW_H
#define STARTWINDOW_H

/**
 * @brief The Start screen for the app. Provides access to main gameplay, credits, and an exit button.
 *
 * @author Steven Luo
 * @date 04/24/25
 */

#include <QWidget>

namespace Ui {
class StartWindow;
}

/**
 * @brief Class representing the Start screen of the app
 */
class StartWindow : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the StartWindow.
     * @param parent Pointer to parent widget
     */
    explicit StartWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor for StartWindow
     */
    ~StartWindow();

signals:
    /**
     * @brief Signal to transition to the main application flow
     */
    void goToMain();

    /**
     * @brief Signal to transition to the credits screen
     */
    void goToCredits();

private slots:
    /**
     * @brief Handles click on the play button to begin
     */
    void on_playButton_clicked();

    /**
     * @brief Handles click on the exit button to close the app
     */
    void on_exitButton_clicked();

    /**
     * @brief Handles click on the credits button to open credits screen
     */
    void on_creditsButton_clicked();

private:
    /**
     * @brief Pointer to the UI object that holds the layout and widgets of StartWindow
     */
    Ui::StartWindow *ui;
};

#endif // STARTWINDOW_H
