#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "custom.h"

#include "game.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    game = new Game();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newgame_item_triggered()
{
    game = new Game(game->GetWidth(), game->GetHeight());
    QMessageBox msg;
    msg.setText(QString("%1x%2").arg(game->GetWidth()).arg(game->GetHeight()));
    msg.exec();
}

void MainWindow::on_easy_item_triggered()
{
    game = new Game(9, 9);
    QMessageBox msg;
    msg.setText(QString("%1x%2").arg(game->GetWidth()).arg(game->GetHeight()));
    msg.exec();
}

void MainWindow::on_medium_item_triggered()
{
    game = new Game(16, 16);
    QMessageBox msg;
    msg.setText(QString("%1x%2").arg(game->GetWidth()).arg(game->GetHeight()));
    msg.exec();
}

void MainWindow::on_hard_item_triggered()
{
    game = new Game(32, 16);
    QMessageBox msg;
    msg.setText(QString("%1x%2").arg(game->GetWidth()).arg(game->GetHeight()));
    msg.exec();
}

void MainWindow::on_custom_item_triggered()
{
    Custom customWindow;
    customWindow.setModal(false);
    customWindow.setFixedSize(220, 150);
    customWindow.exec();

    game = new Game(customWindow.GetWidth(), customWindow.GetHeight());
    QMessageBox msg;
    msg.setText(QString("%1x%2").arg(game->GetWidth()).arg(game->GetHeight()));
    msg.exec();
}

void MainWindow::on_exit_item_triggered()
{
    MainWindow::close();
}

