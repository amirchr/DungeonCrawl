#include "game.h"

using std::cout;
using std::cin;
using std::string;

//const char *LABELS[] = {"Next","button","BUTTon","Previous","butt-on","Button"};

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
	//cbreak();
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

	//setup 'screen'/view window
	WINDOW *textView = newwin(LINES-LINES/4, COLS-2, 0, 1);

	GameState state(textView, nav);
	box(textView, 0, 0);

    wrefresh(textView);

	halfdelay(2);

	while(cont) {
		input = getch();									//take user input
		handleInput(input, &state);							//update state based on input
		drawScreen(&state);									//redraw screen

		if(state.getHP() <= 0) {
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
	case KEY_BACKSPACE:
		state->setHP(0);
		break;
	case KEY_LEFT: {

		state->movePlayerLeft();
		break;
	}
	case KEY_RIGHT: {

		state->movePlayerRight();
		break;
	}
	case KEY_DOWN: {
		state->movePlayerDown();
		break;
	}
	case KEY_UP: {
		state->movePlayerUp();
		break;
	}
	default:
		break;
	}

	if(state->playerInDanger()) {
		drawScreen(state);

		wclear(state->textView);
		wclear(state->nav);
		clear();

		Combat combat;
		combat.start();

		state->removeEnemy();

		drawScreen(state);
	}
}

void drawScreen(GameState *state) {

	//clear and reset border
	wclear(state->textView);
	box(state->textView, 0, 0);

	//place enemies on screen
	int lines, cols, beginx, beginy;
    getmaxyx(state->textView, lines, cols);
    getbegyx(state->textView, beginx, beginy);

    for(int i = 0; i < state->enemies; i++) {
        if(state->enemyCoords[i][0] > 0 && state->enemyCoords[i][1] > 0) {
			mvwaddch(state->textView,
				state->enemyCoords[i][0],
				state->enemyCoords[i][1],
				(chtype)state->floor[state->enemyCoords[i][0]][state->enemyCoords[i][1]]);
		}
    }

	//Update hp bar
	const char *hptext = ("HP: " + std::to_string(state->getHP()) + "  ").c_str();
	updateText(state->nav, hptext, "upperleft");
	box(state->nav, 0, 0);

	//place character token in the middle of the screen
	wmove(state->textView, state->getPlayerY(), state->getPlayerX());
    waddch(state->textView, ACS_PLUS);

	wrefresh(state->textView);
}