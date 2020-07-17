#include "gameState.h"

GameState::GameState(WINDOW *text) {
    hp = 20;
    maxhp = 20;
    textView = text;

    //calculate player position
    int lines, cols, beginx, beginy;
    getmaxyx(textView, lines, cols);
    getbegyx(textView, beginx, beginy);
    playery = (beginy+lines)/2;
    playerx = (beginx+cols)/2;
}

int GameState::getHP() {
    return hp;
}

void GameState::loseHP() {
    hp--;
}

void GameState::gainHP() {
    hp++;
}

void GameState::setHP(int val) {
    hp = val;
}

void GameState::movePlayerRight() {
    int maxx, maxy;
    getmaxyx(textView, maxy, maxx);

    if(playerx < maxx - 1) {
        playerx++;
    }
}

void GameState::movePlayerLeft() {

    if(playerx > 2) playerx--;
}

void GameState::movePlayerUp() {

    if(playery > 2) playery--;
}

void GameState::movePlayerDown() {
    
    int maxx, maxy;
    getmaxyx(textView, maxy, maxx);

    if(playery < maxy - 1) playery++;
}

int GameState::getPlayerX() {   return playerx;     }
int GameState::getPlayerY() {   return playery;     }