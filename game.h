#ifndef GAME_H
#define GAME_H


class Game
{
public:
    Game();
    Game(int w, int h);

    void SetWidth(int value);
    int GetWidth();
    void SetHeight(int value);
    int GetHeight();
private:
    int width, height;
};

#endif // GAME_H
