#include "game.h"

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
