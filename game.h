#ifndef GAME_H
#define GAME_H

#include <QMainWindow>

class Game
{
public:
    Game();
    Game(int w, int h);

    void SetWidth(int value);
    int GetWidth();
    void SetHeight(int value);
    int GetHeight();
    QVector<QVector<bool>> GetMap();
    void NewGame();

private:
    QVector<QVector<int>> map;
    QVector<QVector<int>> mines;
    int width, height;
};

#endif // GAME_H
