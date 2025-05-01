/**
 * Outro window for Brazil.
 *
 * @authors Julia Maia
 * @date 04/24/2025
 *
 * Checked by Julia Maia
 */

#include "braziloutro.h"
#include "ui_braziloutro.h"
#include "mainwindow.h"

BrazilOutro::BrazilOutro(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BrazilOutro)
{
    ui->setupUi(this);

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if(mainWindow) {
        // Connect to main to return to map
        connect(this,
                &BrazilOutro::goToMain,
                mainWindow,
                &MainWindow::returnToMain); }
}

BrazilOutro::~BrazilOutro()
{
    delete ui;
}

void BrazilOutro::on_returnButton_clicked()
{
    emit goToMain();
}
