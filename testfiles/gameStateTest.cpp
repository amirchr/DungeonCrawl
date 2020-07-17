#include <iostream>
#include "../gameState.h"

int main() {

    GameState game(WINDOW buttons[6], WINDOW *textView);

    std::cout << game.getHP();
}