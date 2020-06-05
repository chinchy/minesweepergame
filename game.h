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
    QVector<QVector<int>> GetMap();

    int MineCounterInc();
    void MineCounterDec();
    int CellCounterInc();

    void NewGame();

private:
    QVector<QVector<int>> map;
    int width, height;
    int mine_counter = 0;
    int cell_counter = 0;
    int mine_count = 0;

};

#endif // GAME_H
