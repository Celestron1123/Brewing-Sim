/**
 * The implementation of CreditsWindow
 *
 * @author Steven Luo
 * @date 04/24/2025
 */

#include "creditswindow.h"
#include "ui_creditswindow.h"
#include "mainwindow.h"

CreditsWindow::CreditsWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CreditsWindow)
{
    ui->setupUi(this);

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if(mainWindow) {
        connect(this,
                &CreditsWindow::goToStart,
                mainWindow,
                &MainWindow::goToStart);
    }
}

CreditsWindow::~CreditsWindow()
{
    delete ui;
}

void CreditsWindow::on_backButton_clicked()
{
    emit goToStart();
}

