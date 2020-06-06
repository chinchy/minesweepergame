#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "game.h"

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <QTime>

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
    QVector<QVector<int>> map;
    QTimer *timer;
    bool isTimer = false;
    int time = 0;

    void WinGame();
    void LoseGame();
    void RenderField();
    void OpenCells(QPushButton* btn, int h, int w);
    void update();

private slots:
    void updateTime();
    void on_cell_clicked();
    void on_cell_add_flag();
    void on_newgame_item_triggered();
    void on_easy_item_triggered();
    void on_medium_item_triggered();
    void on_hard_item_triggered();
    void on_custom_item_triggered();
    void on_exit_item_triggered();
    void on_rules_item_triggered();
    void on_about_item_triggered();
};
#endif // MAINWINDOW_H
