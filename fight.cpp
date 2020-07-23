#include "fight.h"

Combat::Combat() {
    srand(time(0));

    monster = Monsters(rand() % 3);
    combatView = newwin(LINES, COLS, 0, 0);
    monsterHP = 20;
    playerHP = 20;
}

int Combat::start() {

    char input = 'y';

    while(input != 'n') {
        mvwprintw(combatView, LINES/2, COLS/2-8, "you see a monster!");
        mvwprintw(combatView, LINES/2+1, COLS/2-7, "press 'n' to run");
        wrefresh(combatView);
        input = getch();
    }

    return 0;
}