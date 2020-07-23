#include "gameState.h"
#include "fight.h"

int startGame();
void updateText(WINDOW *win, const char *msg, const char *placement);
void handleInput(int input, GameState *state);
void drawScreen(GameState *state);