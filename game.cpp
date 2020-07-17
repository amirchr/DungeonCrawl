#include "game.h"

using std::cout;
using std::cin;
using std::string;

const char *LABELS[] = {"Next","button","BUTTon","Previous","butt-on","Button"};

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

	start_color();
	use_default_colors();

	init_pair(1, COLOR_WHITE, COLOR_BLUE);

	refresh();

	bool cont = true;
	int input;

	//setup lower nav window
	WINDOW *nav = newwin(LINES/4, COLS, LINES-(LINES/4), 0);
	box(nav, 0, 0);
	wrefresh(nav);

	//initialize button size, placement, and initial text
	WINDOW *buttons[6];
	/* int startRow, startCol, maxRow, maxCol;
	getbegyx(nav, startRow, startCol);
	getmaxyx(nav, maxRow, maxCol);
	for(int i = 0; i < 2; i++) {
		//int newMaxRow, newMaxCol;
		for(int j = 0; j < 3; j++) {
			int index = i*3+j;
			//create button and place it on lower third of screen
			buttons[index] = newwin(
					maxRow/2-1,
					maxCol/3-1,
					startRow+(1-(i*1))+(i*(maxRow/2)),
					startCol+1+(j*(maxCol/3-1))
				);

			if(index == 0) {
				wattron(buttons[index], A_BOLD | COLOR_PAIR(1));
				int buttBeginY, buttBeginX, maxButtY, maxButtX;
        		getbegyx(buttons[index], buttBeginY, buttBeginX);
				getmaxyx(buttons[index], maxButtY, maxButtX);
        		for(int i = buttBeginY; i < LINES; i++) {              //scan over all lines in button[0] to draw bg color
					mvwhline(buttons[index], i, 0, ' ', COLS);
				}
			}
			updateText(buttons[index], LABELS[index], "center");
			wattroff(buttons[index], COLOR_PAIR(1));
			box(buttons[index], 0, ' ');
			
			//add text and place in the middle of buttons
			wattroff(buttons[index], A_BOLD);
		}
	} */
	//wrefresh(nav);
	/*wrefresh(buttons[0]);
	wrefresh(buttons[1]);
	wrefresh(buttons[2]);
	wrefresh(buttons[3]);
	wrefresh(buttons[4]);
	wrefresh(buttons[5]);*/

	//setup 'screen'/view window
	WINDOW *textView = newwin(LINES-LINES/4-1, COLS-2, 1, 1);
	GameState state(textView);
	box(textView, 0, 0);
	drawScreen(textView, nav, state);
	updateText(textView, "Welcome to the Game >:)", "center");

	halfdelay(2);
	getch();

	std::cout << state.getHP();

	while(cont) {
		input = getch();									//take user input
		handleInput(input, &state);							//update state based on input
		drawScreen(textView, nav, state);					//redraw screen

		if(state.getHP() == 0) {
			cont = false;
		}
	}

	clear();
	endwin();

	return -1;
}

void updateText(WINDOW *win, const char *msg, const char *placement) {

	int maxRow, maxCol;
	getmaxyx(win, maxRow, maxCol);
	if(strcmp(placement, "upperleft") == 0) {
		mvwprintw(win, 1, 1, msg);
	} else if(strcmp(placement, "upperright") == 0) {
		mvwprintw(win, 1, maxCol-1, msg);
	} else if(strcmp(placement, "lowerleft") == 0) {
		mvwprintw(win, maxRow-1, 1, msg);
	} else if(strcmp(placement, "lowerright") == 0) {
		mvwprintw(win, maxRow-1, maxCol-1, msg);
	} else {
		mvwprintw(win, maxRow/2, (maxCol-strlen(msg))/2, msg);
	}
	wrefresh(win);
}

void handleInput(int input, GameState *state) {

	switch(input) {
	case 'w':
		state->loseHP();
		break;
	case 's':
		state->gainHP();
		break;
	case KEY_BACKSPACE:
		state->setHP(0);
		break;
	/* case KEY_LEFT: {
		WINDOW *butt = state->getButton(state->highlightedButton);
		wattrset(butt, 0);
		updateText(butt, LABELS[state->highlightedButton], "center");

		if(state->highlightedButton%3 == 0) state->highlightedButton += 2;
		else state->highlightedButton--;

		WINDOW * newButt = state->getButton(state->highlightedButton);
		wattron(newButt, A_BOLD | COLOR_PAIR(1));
		updateText(newButt, LABELS[state->highlightedButton], "center");

		break;
	}
	case KEY_RIGHT: {
		WINDOW *butt = state->getButton(state->highlightedButton);
		wattrset(butt, 0);
		for(int i = 0; i < LINES; i++) {              //scan over all lines in button[] to draw bg color
			mvwhline(butt, i, 0, ' ', COLS);
		}
		box(butt, 0, ' ');
		updateText(butt, LABELS[state->highlightedButton], "center");

		if((state->highlightedButton+1)%3 == 0) state->highlightedButton -= 2;
		else state->highlightedButton++;

		WINDOW * newButt = state->getButton(state->highlightedButton);
		wattron(newButt, A_BOLD | COLOR_PAIR(1));
		updateText(newButt, LABELS[state->highlightedButton], "center");

		break;
	}
	case KEY_DOWN: {
		WINDOW *butt = state->getButton(state->highlightedButton);
		wattrset(butt, 0);
		updateText(butt, LABELS[state->highlightedButton], "center");

		if(state->highlightedButton >= 3) state->highlightedButton -= 3;
		else state->highlightedButton += 3;

		WINDOW * newButt = state->getButton(state->highlightedButton);
		wattron(newButt, A_BOLD | COLOR_PAIR(1));
		updateText(newButt, LABELS[state->highlightedButton], "center");

		break;
	}
	case KEY_UP: {
		WINDOW *butt = state->getButton(state->highlightedButton);
		wattrset(butt, 0);
		updateText(butt, LABELS[state->highlightedButton], "center");

		if(state->highlightedButton <= 2) state->highlightedButton += 3;
		else state->highlightedButton -= 3;

		WINDOW * newButt = state->getButton(state->highlightedButton);
		wattron(newButt, A_BOLD | COLOR_PAIR(1));
		updateText(newButt, LABELS[state->highlightedButton], "center");

		break;
	} */
	default:
		break;
	}
}

void drawScreen(WINDOW *win, WINDOW *nav, GameState state) {

	//clear and reset border
	wclear(win);
	box(win, 0, 0);

	//Update hp barr
	const char *hptext = ("HP: " + std::to_string(state.getHP())).c_str();
	updateText(win, hptext, "upperleft");
}