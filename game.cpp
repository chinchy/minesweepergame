#include "game.h"

#include <QPushButton>
#include <QRandomGenerator>
#include <QDebug>

Game::Game(){
    this->width = 9;
    this->height = 9;
}

Game::Game(int w, int h){
    this->width = w;
    this->height = h;
}

int Game::GetWidth(){
    return this->width;
}

void Game::SetWidth(int value){
    this->width = value;
}

int Game::GetHeight(){
    return this->height;
}

void Game::SetHeight(int value){
    this->height = value;
}

QVector<QVector<int>> Game::GetMap(){
    return this->map;
}

void Game::NewGame(){
    QVector<QVector<int>> tmp_map(height, QVector<int>(width, -2));
    QVector<QVector<int>> tmp_mines(height, QVector<int>(width, 0));

    QRandomGenerator generator;
    std::uniform_int_distribution<int> distribution(1, 100);

    for (int h = 0; h < height; h++){
        for (int w = 0; w < width; w++) {
            bool isMine = distribution(*QRandomGenerator::global()) < 15;

            if (isMine){
                tmp_map[h][w] = -1;
                for (int i=-1; i<2; i++){
                    for (int j=-1; j<2; j++){
                        if ((h+i < height && h+i >= 0) && (w+j < width && w+j >= 0)){
                            if (tmp_map.at(h+i).at(w+j) == -2)
                                tmp_mines[h+i][w+j]++;
                            else
                                if (tmp_map.at(h+i).at(w+j) >=0)
                                    tmp_mines[h+i][w+j]++;
                        }
                    }
                }
            }
        }
    }

    for (int h = 0; h < height; h++){
        for (int w = 0; w < width; w++) {
            if (tmp_map.at(h).at(w) != -1)
                tmp_map[h][w] = tmp_mines.at(h).at(w);
        }
    }

    map = tmp_map;

    qDebug("===Map===");
    for (QVector<QVector<int>>::iterator xIter = map.begin(); xIter != map.end(); xIter++){
        qDebug() << (*xIter);
    }
}
