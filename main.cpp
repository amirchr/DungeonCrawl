//In Notepad++: Ctrl-6 to compile, Ctrl-7 to compile and run

#include <ncurses.h>
#include <unistd.h>
#include <iostream>

using std::cout;
using std::cin;
using std::string;

int game();

int main() {

	bool cont = true;
	char input = 'n';

	cout << "A lion head asks you, \"Would you like to enter the dungeon?\"\n(y/n)\n";
	cin >> input;
	cout << "\n";
	
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
	
		int result = game();
	
		if(result == -1) {
			cout << "\e[2J\e[HSorry! better luck next time.\nEnter X to leave... Enter R to try again...\n";
			cin >> input;
			cout << "\n";
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

int game() {

	initscr();
	clear();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	int maxRow,maxCol;
	getmaxyx(stdscr,maxRow,maxCol);

	WINDOW *win = newwin(LINES/3, COLS, LINES-(LINES/3), 0);
	box(win, 0, 0);
	refresh();
	wrefresh(win);
	getch();

	mvprintw(LINES/3, COLS/2.5,"Welcome to the game >:)");
	refresh();
	getch();
	clear();
	
	endwin();

	return -1;
}
