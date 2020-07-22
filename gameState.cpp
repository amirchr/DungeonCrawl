#include "gameState.h"

GameState::GameState(WINDOW *text) {
    srand(time(0));

    hp = 20;
    maxhp = 20;
    textView = text;

    //calculate player position
    int lines, cols, beginx, beginy;
    getmaxyx(textView, lines, cols);
    getbegyx(textView, beginx, beginy);
    playery = (beginy+lines)/2;
    playerx = (beginx+cols)/2;

    for(int i = 0; i < lines; i++) {
        for(int j = 0; j < cols; j++) {
            floor[i][j] = ' ';
        }
    }

    //Fill floor with enemies, randomly placed
    enemies = 0;
    while(enemies < 5) {
        int x = (rand()%(cols-2)),
            y = (rand()%(lines-2))+1;
        if(floor[y][x] != 'A') {
            floor[y][x] = 'A';
            enemyCoords[enemies][0] = y;
            enemyCoords[enemies][1] = x;
            enemies++;
        }
    }
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

    if(playerx < maxx - 2) {
        playerx++;
    }
}

void GameState::movePlayerLeft() {

    if(playerx > 1) playerx--;
}

void GameState::movePlayerUp() {

    if(playery > 1) playery--;
}

void GameState::movePlayerDown() {
    
    int maxx, maxy;
    getmaxyx(textView, maxy, maxx);

    if(playery < maxy - 2) playery++;
}

int GameState::getPlayerX() {   return playerx;     }
int GameState::getPlayerY() {   return playery;     }

bool GameState::playerInDanger() {
    for(int i = 0; i < enemies; i++) {
        if(enemyCoords[i][0] == playery && enemyCoords[i][1] == playerx)
            return true;
    }

    return false;
}