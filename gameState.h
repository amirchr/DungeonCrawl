#include <unistd.h>
#include <iostream>
#include <curses.h>
#include <ncurses.h>
#include <string.h>
#include <ctime>

class GameState {
    private:
        int hp;
        int maxhp;
        int playerx, playery;

    public:
        char floor[300][300];
        int enemyCoords[5][2];     //TODO: add getter and setter functions for these
        int enemies;
        WINDOW *textView, *nav;

        GameState(WINDOW *text, WINDOW *nav);
        void loseHP();
        void gainHP();
        int getHP();
        void setHP(int val);
        void movePlayerRight();
        void movePlayerLeft();
        void movePlayerUp();
        void movePlayerDown();
        int getPlayerX();
        int getPlayerY();
        bool playerInDanger();
        void removeEnemy();
};