#include <curses.h>
#include <ncurses.h>

class GameState {
    public:
        GameState(WINDOW *text, WINDOW *butts[]);
        void loseHP();
        void gainHP();
        int getHP();
        void setHP(int val);
        int highlightedButton;
        WINDOW *getButton(int index);
    private:
        GameState();
        WINDOW *textView;
        int hp;
        int maxhp;
        WINDOW *buttons[6];
};