#ifndef _GAME_OF_LIFE_H_
#define _GAME_OF_LIFE_H_

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class game_of_life {
private:
	static const unsigned int COLS = 10; //40
	static const unsigned int ROWS = 10; //20
	//bool cells[ROWS][COLS];
	
	bool this_generation[ROWS][COLS];
	bool welcoming_the_next_generation[ROWS][COLS];
	
	bool random_value();
	bool cell_taken(int j, int i);
	int reloads = 0;

	bool creation;
public:
	//game_of_life();
	void next_generation();
	void draw();
};

#endif

