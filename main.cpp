//In Notepad++: Ctrl-6 to compile, Ctrl-7 to compile and run

#include <iostream>

auto& cout = std::cout;
auto& cin = std::cin;
typedef std::string string;

int main() {
	bool start = true;
	
	while(start) {
	
		bool cont = false;
		char input;

		cout << "\nWould you like to enter the dungeon?\n";
		cin >> input;
	
		if(toupper(input) == 'Y') cont = true;
	
		while(cont) {
			cout << "\nWould you still like to be here?\n";
			cin >> input;
	
			if(toupper(input) == 'N') cont = false;
		}
	
		cout << "\nEnter X to leave... Enter R to try again...\n";
		cin >> input;
	
		if(toupper(input) == 'X') {
			start = false;
		}
	}
	return 0;
}
