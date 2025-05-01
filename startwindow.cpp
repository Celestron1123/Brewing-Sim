/**
 * The implementation of StartWindow
 *
 * @author Steven Luo
 * @date 04/24/2025
 */

#include "startwindow.h"
#include "ui_startwindow.h"
#include "mainwindow.h"

StartWindow::StartWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StartWindow)
{
    ui->setupUi(this);

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if(mainWindow) {
        connect(this,
                &StartWindow::goToMain,
                mainWindow,
                &MainWindow::returnToMain);

        connect(this,
                &StartWindow::goToCredits,
                mainWindow,
                &MainWindow::goToCredits);
    }
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::on_playButton_clicked()
{
    emit goToMain();
}

void StartWindow::on_exitButton_clicked()
{
    QApplication::quit();
}


void StartWindow::on_creditsButton_clicked()
{
    emit goToCredits();
}

