#include "game_of_life.h"
#include <iostream>
#include <stdlib.h>
#include<ctime>

//Private

bool game_of_life::cell_taken(int x, int y) {
	return this_generation[x][y];
}

bool game_of_life::random_value() {
	return rand() % 2;
}

//Public

void game_of_life::next_generation() {

	bool passing_info_to_stop_checking_around_it = false;

	if (creation) { //first generation is created
		for (int i = 0; i < COLS; i++) {
			for (int j = 0; j < ROWS; j++) {
				welcoming_the_next_generation[j][i] = random_value();
			}
		}
		creation = false;
	}
	else {
		int neighbor_counter = 0;

		/*New generation becoming old*/
		for (int y = 0; y < COLS; ++y) {
			for (int x = 0; x < ROWS; ++x) {
				if (welcoming_the_next_generation[x][y]) {
					this_generation[x][y] = true;
				}
				else {
					this_generation[x][y] = false;
				}
				welcoming_the_next_generation[x][y] = false;
			}
		}

		for (int y = 0; y < COLS; ++y) {
			passing_info_to_stop_checking_around_it = false;
			neighbor_counter = 0;
			for (int x = 0; x < ROWS; ++x) {
				passing_info_to_stop_checking_around_it = false;
				neighbor_counter = 0;
				if (!this_generation[x][y]) continue; //Does the cell even exist?
				else {

					for (int y1 = -1; y1 <= 1; ++y1) {
						for (int x1 = -1; x1 <= 1; ++x1) {
							/*Imminent death check*/
							if (neighbor_counter == 4) {
								passing_info_to_stop_checking_around_it = true;
								break;
							}

							if (y + y1 >= 0 and x + x1 >= 0 and y + y1 < COLS and x + x1 < ROWS) {
								if (x + x1 == x and y + y1 == y) continue;

								if (cell_taken(y + y1, x + x1)) neighbor_counter++;
							}
						}
						if (passing_info_to_stop_checking_around_it) {
							break;
						}
					}
				}

				if(neighbor_counter == 3 or neighbor_counter == 2 or !passing_info_to_stop_checking_around_it){
					/*CELL LIVES ON (WITH NO BENEFITS)*/
					if (neighbor_counter == 2) {
						welcoming_the_next_generation[x][y] = true;
						continue;
					}
					passing_info_to_stop_checking_around_it = false;
					/*CELL LIVES ON (WITH BENEFITS (NEW CELL IS BORN))*/
					if (neighbor_counter == 3) {
						welcoming_the_next_generation[x][y] = true;
						for (int y1 = -1; y1 <= 1; ++y1) {
							for (int x1 = -1; x1 <= 1; ++x1) {
								if (y + y1 >= 0 and x1 + x >= 0 and y + y1 < COLS and x + x1 < ROWS) {
									if (cell_taken(y + y1, x + x1)) continue;
									else {
										welcoming_the_next_generation[x + x1][y + y1] = true;
										passing_info_to_stop_checking_around_it = true;
										break;
									}
								}
							}
							if (passing_info_to_stop_checking_around_it) {
								break;
							}
						}
					}
				}
				else {
					/*DEATH*/
					welcoming_the_next_generation[x][y] = false;
					continue;
				}
			}
		}
	}
}

void game_of_life::draw() {
	system("cls");

		for (int i = 0; i < COLS; i++) {
			for (int j = 0; j < ROWS; j++) {

				if (welcoming_the_next_generation[j][i]) {
					std::cout << "*";
				}
				else {
					std::cout << "-";
				}
			}
			std::cout << std::endl;
		}
}