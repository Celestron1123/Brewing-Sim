#ifndef BRAZILOUTRO_H
#define BRAZILOUTRO_H

/**
 * Outro window for Brazil.
 *
 * @authors Julia Maia
 * @date 04/24/2025
 *
 * Checked by Julia Maia
 */

#include <QWidget>

namespace Ui {
class BrazilOutro;
}

class BrazilOutro : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief BrazilOutro constructor
     * @param parent
     */
    explicit BrazilOutro(QWidget *parent = nullptr);

    /**
     * BrazilOutro destructor
     */
    ~BrazilOutro();

private slots:
    /**
     * @brief on_returnButton_clicked - Returns to the main window once clicked
     */
    void on_returnButton_clicked();

signals:

    /**
     * @brief goToMain - Emits a signal to return to the main window.
     */
    void goToMain();

private:
    Ui::BrazilOutro *ui;
};

#endif // BRAZILOUTRO_H
