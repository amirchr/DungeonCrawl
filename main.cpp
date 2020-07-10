#include <curses.h>
#include <ncurses.h>
#include <unistd.h>
#include <iostream>
#include <string.h>

using std::cout;
using std::cin;
using std::string;

int startGame();
void updateText();

int main() {

	bool cont = false;
	char input = 'n';

	cout << "A lion head asks you, \"Would you like to enter the dungeon?\"\n(y/n)\n";
	cin >> input;
	cout << "\n";
	
	if(tolower(input) == 'y') {
		cont = true;
	}

	while(cont) {	
	
		cout << "Good luck...";
		/*cout.flush();
		sleep(1);
		cout << ".";
		cout.flush();
		sleep(1);
		cout << ".";
		cout.flush();
		sleep(1);
		cout << ".\n";*/
	
		int result = startGame();
	
		if(result == -1) {
			cout << "\e[2J\e[H\n\nSorry! better luck next time.\n\n\n";//\nEnter X to leave... Enter R to try again...\n";
			//cin >> input;
			//cout << "\n";
			cont = false;
		} else {
			cout << "well done! here's a cookie for beating the dungeon.\n";
			cont = false;
		}
	
		if(toupper(input) == 'X') {
			cont = false;
		}
	}

	return 0;
}

int startGame() {

	//initial ncurses setup settings
	initscr();
	clear();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	refresh();

	//setup lower nav window
	WINDOW *nav = newwin(LINES/3, COLS, LINES-(LINES/3), 0);
	box(nav, 0, 0);
	wrefresh(nav);

	//initialize button size, placement, and initial text
	WINDOW *buttons[6];
	int startRow, startCol, maxRow, maxCol;
	const char *labels[] = {"Next","button","BUTTon","Previous","butt-on","Button"};
	getbegyx(nav, startRow, startCol);
	getmaxyx(nav, maxRow, maxCol);
	wattron(buttons[0], A_BOLD);
	for(int i = 0; i < 2; i++) {
		int newMaxRow, newMaxCol;
		for(int j = 0; j < 3; j++) {
			int index = i*3+j;
			//create button and place it on lower third of screen
			buttons[index] = newwin(
					maxRow/2-1,
					maxCol/3-1,
					startRow+1+(i*(maxRow/2)),
					startCol+1+(j*(maxCol/3-1))
				);
			box(buttons[index], 0, ' ');

			if(index == 0) wattron(buttons[index], A_BOLD);
			//add text and place in the middle of buttons
			getmaxyx(buttons[index], newMaxRow, newMaxCol);
			mvwprintw(buttons[index], newMaxRow/2-1, newMaxCol/2-strlen(labels[index])/2, labels[index]);
			wrefresh(buttons[index]);
		}
	}

	//setup 'screen'/view window
	WINDOW *textView = newwin(LINES-LINES/3-1, COLS-2, 1, 1);
	box(textView, 0, 0);
	const char *msg = "Welcome to the Game >:)";
	mvwprintw(textView, (LINES-LINES/3-1)/2, ((COLS)/2-strlen(msg)/2), msg);
	wrefresh(textView);

	getch();
	wrefresh(textView);

	msg = "I know it's not much yet... I'm working on it";
	mvwprintw(textView, (LINES-LINES/3-1)/2, ((COLS)/2-strlen(msg)/2), msg);
	wrefresh(textView);
	getch();
	clear();
	
	endwin();

	return -1;
}

void updateText() {

	
}