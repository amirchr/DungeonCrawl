#include <iostream>
#include "../gameState.h"

int main() {

    initscr();
	clear();
	cbreak();
    curs_set(0);

    int scrlines = LINES;
    int scrcols = COLS;

    WINDOW *textView = newwin(LINES, COLS, 0, 0);
    box(textView, 0, 0);

    GameState game(textView);

    int lines, cols, beginx, beginy;
    getmaxyx(textView, lines, cols);
    getbegyx(textView, beginx, beginy);

    for(int i = 0; i < lines; i++) {
        for(int j = 0; j < cols; j++) {
            mvwaddch(textView, i, j, (chtype)game.floor[i][j]);
        }
    }

    refresh();
    wrefresh(textView);
    getch();

    endwin();
}