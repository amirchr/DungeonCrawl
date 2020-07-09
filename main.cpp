//In Notepad++: Ctrl-6 to compile, Ctrl-7 to compile and run

#include <ncurses.h>
#include <unistd.h>
#include <iostream>

using std::cout;
using std::cin;
using std::string;

int game();

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
	
		int result = game();
	
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

void initializeUI(WINDOW view, WINDOW buttons[]) {

	
}

int game() {

	WINDOW *buttons[6];
	WINDOW *textView;

	//initial ncurses setup settings
	initscr();
	clear();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);

	//setup lower nav window
	WINDOW *nav = newwin(LINES/3, COLS, LINES-(LINES/3), 0);
	box(nav, 0, 0);
	refresh();
	wrefresh(nav);

	//initialize button size, placement, and initial text
	int startRow, startCol, maxRow, maxCol;
	getbegyx(nav, startRow, startCol);
	getmaxyx(nav, maxRow, maxCol);
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

			//add text and place in the middle of buttons
			getmaxyx(buttons[index], newMaxRow, newMaxCol);
			mvwprintw(buttons[index], newMaxRow/2-1, newMaxCol/2-3, "Button");
			wrefresh(buttons[index]);
		}
	}

	//setup 'screen'/view window
	textView = newwin(LINES-LINES/3-1, COLS-2, 1, 1);
	box(textView, 0, 0);
	string mess = "Welcome to the Game >:)";
	const char *msg = mess.c_str();
	mvwprintw(textView, (LINES-LINES/3-1)/2, ((COLS)/2-mess.length()/2), msg);
	refresh();
	wrefresh(textView);

	getch();
	werase(textView);
	box(textView, 0, 0);

	mess = "I know it's not much yet... I'm working on it";
	msg = mess.c_str();
	mvwprintw(textView, (LINES-LINES/3-1)/2, ((COLS)/2-mess.length()/2), msg);
	wrefresh(textView);
	getch();
	clear();
	
	endwin();

	return -1;
}
