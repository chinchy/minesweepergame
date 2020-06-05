#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "game.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Game *game;

private:
    Ui::MainWindow *ui;
    void RenderField();

private slots:
    void on_cell_clicked();
    void on_newgame_item_triggered();
    void on_easy_item_triggered();
    void on_medium_item_triggered();
    void on_hard_item_triggered();
    void on_custom_item_triggered();
    void on_exit_item_triggered();
};
#endif // MAINWINDOW_H
