#ifndef CARIBBEANINTRO_H
#define CARIBBEANINTRO_H

/**
 * @brief The Intro screen for the Caribbean section of the app.
 *
 * @author Steven Luo
 * @date 04/24/25
 */

#include <QWidget>

namespace Ui {
class CaribbeanIntro;
}

/**
 * @brief Class representing the Intro screen for the Caribbean section of the app
 */
class CaribbeanIntro : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the CaribbeanIntro window.
     * @param parent Pointer to parent widget
     */
    explicit CaribbeanIntro(QWidget *parent = nullptr);

    /**
     * @brief Destructor for CaribbeanIntro
     */
    ~CaribbeanIntro();

signals:
    /**
     * @brief Signal to transition to the CaribbeanHarvest screen
     */
    void goToHarvest();

private slots:
    /**
     * @brief Handles click on the start button to begin the Caribbean section of the app
     */
    void on_start_clicked();

private:
    /**
     * @brief Pointer to the UI object that holds the layout and widgets of CaribbeanIntro
     */
    Ui::CaribbeanIntro *ui;
};

#endif // CARIBBEANINTRO_H
