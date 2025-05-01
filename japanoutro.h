#ifndef JAPANOUTRO_H
#define JAPANOUTRO_H

#include <QWidget>

namespace Ui {
/**
 * Japan outro window
 *
 * @author Elijah Potter
 * @date 4/24/25
 */
class JapanOutro;
}

class JapanOutro : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief JapanOutro constructor
     * @param parent window pointer
     */
    explicit JapanOutro(QWidget *parent = nullptr);

    /**
     * Japan destructor
     */
    ~JapanOutro();

private slots:
    /**
     * @brief Handles goint to the next screen
     */
    void on_pushButton_clicked();

    /**
     * @brief Handles the keg spout being clicked
     */
    void on_pour_clicked();

signals:
    /**
     * @brief signals to go back to main
     */
    void goToMain();

private:
    /**
     * @brief ui pointers
     */
    Ui::JapanOutro *ui;
};

#endif // JAPANOUTRO_H
