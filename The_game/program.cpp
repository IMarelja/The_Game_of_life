#include <iostream>
#include <string>
#include <fstream>
#include "game_of_life.h"
#include <windows.h>

using namespace std;

int main() {
	//srand(time(0));

	game_of_life the_game;

	bool again;
	do {
		the_game.next_generation();
		the_game.draw();
		
		cout << "Again (1/0): ";
		cin >> again;
	} while (again);

	HWND hwnd = GetConsoleWindow();
	if (hwnd != NULL) {
		PostMessage(hwnd, WM_CLOSE, 0, 0);
	}

	return 0;
}