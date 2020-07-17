#include "gameState.h"

int startGame();
void updateText(WINDOW *win, const char *msg, const char *placement);
void handleInput(int input, GameState *state);
void drawScreen(WINDOW *textView, WINDOW *nav, GameState state);