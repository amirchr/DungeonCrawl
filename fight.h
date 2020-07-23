#include <ctime>
#include <iostream>
#include <curses.h>
#include <ncurses.h>
#include <string.h>

enum Monsters {Skeleton, Ogre, GiantRat};

class Combat {
private:
    Monsters monster;

public:
    Combat();
    int start();
    WINDOW *combatView;
    int monsterHP, playerHP;
};

