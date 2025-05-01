#ifndef MEXICOINTRO_H
#define MEXICOINTRO_H
/**
 * @class MexicoIntro
 * @brief Mexico widget in which the user is introduced to the history and distillation process of tequila.
 *
 * @authors Ryan Hamerman, Steven Luo, Julia Maia, Yudith Mendoza, William Ngo, Elijah Potter
 */

#include <QWidget>

namespace Ui {
class MexicoIntro;
}

class MexicoIntro : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     */
    explicit MexicoIntro(QWidget *parent = nullptr);
    /**
     * @brief Destructor
     */
    ~MexicoIntro();

private:
    Ui::MexicoIntro *ui;

private slots:
    /**
     * @brief Handles when user clicks start button.
     * Emits signal for next widget.
     */
    void onStartClicked();

signals:
    /**
     * @brief Calls for next widget.
     */
    void goToHarvest();
};

#endif // MEXICOINTRO_H
