#ifndef JAPANINTRO_H
#define JAPANINTRO_H

/**
 * Japan Intro window
 *
 * @author Elijah Potter
 * @date 4/24/25
 */

#include <QWidget>

namespace Ui {
class JapanIntro;
}

/**
 * @brief The JapanIntro class
 */
class JapanIntro : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief JapanIntro constructor
     * @param parent window pointer
     */
    explicit JapanIntro(QWidget *parent = nullptr);

    /**
     * Japan destructor
     */
    ~JapanIntro();

private slots:
    /**
     * @brief Handles going to the next screen
     */
    void on_start_clicked();

signals:
    /**
     * @brief Signals to go to the next screen
     */
    void goToBrew();

private:
    /**
     * @brief ui pointer
     */
    Ui::JapanIntro *ui;
};

#endif // JAPANINTRO_H
