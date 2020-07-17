#include <string.h>
#include <unistd.h>
#include <iostream>
#include <curses.h>
#include <ncurses.h>

class GameState {
    public:
        GameState(WINDOW *text);
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
    private:
        GameState();
        WINDOW *textView;
        int hp;
        int maxhp;
        int playerx, playery;
};