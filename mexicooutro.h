#ifndef MEXICOOUTRO_H
#define MEXICOOUTRO_H
/**
 * @class MexicoOutro
 * @brief Mexico widget in which the user is shown the distillation and bottling process of tequila production.
 *
 * @authors Ryan Hamerman, Steven Luo, Julia Maia, Yudith Mendoza, William Ngo, Elijah Potter
 */

#include <QWidget>

namespace Ui {
class MexicoOutro;
}

class MexicoOutro : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     */
    explicit MexicoOutro(QWidget *parent = nullptr);
    /**
     * @brief Destructor
     */
    ~MexicoOutro();

private:
    Ui::MexicoOutro *ui;

private slots:
    /**
     * @brief Handles when user clicks "Back to Main" button.
     * Emits signal for next widget.
     */
    void onBtnClicked();
    /**
     * @brief Handles when user clicks on barrel nozzle
     * Updates UI to show filled bottle.
     */
    void onPourClicked();

signals:
    /**
     * @brief Calls for main window widget.
     */
    void goToMain();

};

#endif // MEXICOOUTRO_H
