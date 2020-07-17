#include "gameState.h"

GameState::GameState(WINDOW *text) {
    hp = 20;
    maxhp = 20;
    //highlightedButton = 0;
    textView = text;

    /* for(int i = 0; i < 6; i++) {            //TODO: change hardcoded 6 to whatever length of butts is
        buttons[i] = butts[i];
    } */
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

/* WINDOW *GameState::getButton(int index) {
    return buttons[index];
} */