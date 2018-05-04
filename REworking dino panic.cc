#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <ncurses.h>
#include <utility>
#include <limits>
#include <vector>
#include <queue>
#include <set>
#include "splash.h"
using namespace std;

class Monster;

const unsigned char OPEN = ' '; //An open space
const unsigned char WALL = '#'; //A wall space; impassable
const unsigned char MONSTER = 'M'; //Eats herbivores

//Globals holding game state
int SIZE_X=SIZE_Y=40; //Dimensions of the world
int cursor_x, cursor_y; //Cursor for drawing stuff
unsigned char* world; //A character array holding our world
vector<Monster> monsters;
bool game_on; //Holds if the simulation is running

const int UP = 65; //Key code for up arrow
const int DOWN = 66;
const int LEFT = 68;
const int RIGHT = 67;

//2D to 1D array mapping
//NOTE: creates a circular array
//For example, access the world location (3,2) like this:
//  world[index(3,2)]
int index(int i, int j) {
	while (i < 0) i += SIZE_X;
	while (j < 0) j += SIZE_Y;
	if (i >= SIZE_X) i %= SIZE_X;
	if (j >= SIZE_Y) j %= SIZE_Y;
	return (i * SIZE_Y + j);
}

class Monster {
  public:
	Monster() {}
	Monster(int new_x, int new_y) : x(new_x), y(new_y) {}
	int x = 0, y = 0; //Location
	void think() { //AI For the plant
		int new_x = x + rand() % 3 - 1;
		int new_y = y + rand() % 3 - 1;
			if (world[index(new_x, new_y)] == OPEN) {
				world[index(new_x, new_y)] = MONSTER;
				world[index(x, y)] = OPEN;
				x = new_x;
				y = new_y;
			}
		}
	}
};
const int MONSTER_NUMBER = 5;
//Builds an empty world with walls on the edges and open squares in the middle
//Randomly populate it with herbs, herbivores, and carnivores
void reset_world() {
	for (int i = 0; i < SIZE_X; i++) {
		for (int j = 0; j < SIZE_Y; j++) {
			if (i == 0 || j == 0 || i == SIZE_X - 1 || j == SIZE_Y - 1) //Is edge
				world[index(i, j)] = WALL;
			else
				world[index(i, j)] = OPEN;
 			else if (world[index(i, j)] == OPEN && rand() % 100 < MONSTER_NUMBER) {
				world[index(i, j)] = MONSTER;
				monsters.push_back(Monster(i, j));
			}
		}
	}
}

//Prints the entire world, bolding the square the cursor is on
void print_world() {
	for (int i = 0; i < SIZE_X; i++) {
		for (int j = 0; j < SIZE_Y; j++) {
			if (i == cursor_x && j == cursor_y)
				attron(A_UNDERLINE | A_BOLD);
			int color = 1;
			if (world[index(i, j)] == WALL)
				color = 5;
				color = 4;
			else if (world[index(i, j)] == MONSTER)
				color = 6;
			attron(COLOR_PAIR(color));
			mvaddch(i, j, world[index(i, j)]);
			attroff(COLOR_PAIR(color));
			attroff(A_UNDERLINE | A_BOLD);
		}
	}
}

int main() {
	//Initialize random number generator
	srand(time(NULL));

	cout << "How big a world do you want? (Enter x size followed by y then hit return): ";
	cin >> SIZE_Y >> SIZE_X; //Everything is backwards (x and y) in NCURSES
	if (!cin || SIZE_X < MIN_SIZE || SIZE_Y < MIN_SIZE) {
		cout << "Error: world size must be at least " << MIN_SIZE << " in each dimension.\n";
		return 1;
	}

	//Set up NCURSES
	initscr();//Start curses mode
	start_color(); //Enable Colors if possible
	init_pair(1, COLOR_WHITE, COLOR_BLACK); //Set up some color pairs
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_RED, COLOR_BLACK);
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
	clear();
	noecho();
	cbreak();
	timeout(TIMEOUT); //Set a max delay for key entry

	//Splash Screen
	world = new unsigned char[SIZE_X * SIZE_Y];
	reset_world();
	//MAIN LOOP
	int frame = 0;
	cursor_x = SIZE_X / 2, cursor_y = SIZE_Y / 2; //Cursor for drawing stuff
	game_on = false;
	while (true) {
		if (!game_on)
			mvprintw(SIZE_X, 0, "Design Mode - Game Paused                                        ");
		else
			mvprintw(SIZE_X, 0, "Game Running. Herbs: %i Herbivores: %i Carnivores: %i Frame: %i", herbs.size(), herbivores.size(), carnivores.size(), frame++);
		mvprintw(SIZE_X + 1, 0, "Use arrow keys to move the cursor around");
		mvprintw(SIZE_X + 2, 0, "Type Space to clear the square or set a wall");
		mvprintw(SIZE_X + 3, 0, "Type ~ to place a water");
		mvprintw(SIZE_X + 4, 0, "Type ! to place an Herb");
		mvprintw(SIZE_X + 5, 0, "Type H to place an Herbivore");
		mvprintw(SIZE_X + 6, 0, "Type R to place a Carnivore");
		mvprintw(SIZE_X + 7, 0, "Type Enter to run or pause the game");
		mvprintw(SIZE_X + 8, 0, "Type Q to quit");
		int ch = getch(); // Wait for user input, with TIMEOUT delay
		if (ch == 'q' || ch == 'Q') break;
		else if (ch == ' ' || ch == '#') {
			if (world[index(cursor_x, cursor_y)] == OPEN)
				world[index(cursor_x, cursor_y)] = WALL;
			else if (world[index(cursor_x, cursor_y)] == WALL)
				world[index(cursor_x, cursor_y)] = OPEN;
			//TODO: Be able to clear other things from the world
		} else if (ch == '!' || ch == '1') {
			if (world[index(cursor_x, cursor_y)] == OPEN) {
				world[index(cursor_x, cursor_y)] = HERB;
				herbs.push_back(Herb(cursor_x, cursor_y));
			}
		} else if (ch == 'h' || ch == 'H') {
			if (world[index(cursor_x, cursor_y)] == OPEN) {
				world[index(cursor_x, cursor_y)] = HERBIVORE;
				herbivores.push_back(Herbivore(cursor_x, cursor_y));
			}
		} else if (ch == 'r' || ch == 'R') {
			if (world[index(cursor_x, cursor_y)] == OPEN) {
				world[index(cursor_x, cursor_y)] = CARNIVORE;
				carnivores.push_back(Carnivore(cursor_x, cursor_y));
			}
		} else if (ch == '`' || ch == '~') {
			if (world[index(cursor_x, cursor_y)] == OPEN) {
				world[index(cursor_x, cursor_y)] = WATER;
			}
		}
		//Handle arrow keys, the NCURSES #defs don't work here for some reason
		//KEY_UP, for example, is set to 0403 (259), not 65
		else if (ch == RIGHT) {
			cursor_y++;
			if (cursor_y >= SIZE_Y) cursor_y = SIZE_Y - 1; //Clamp value
		} else if (ch == LEFT) {
			cursor_y--;
			if (cursor_y < 0) cursor_y = 0;
		} else if (ch == UP) { //Should be KEY_UP, grr
			cursor_x--;
			if (cursor_x < 0) cursor_x = 0;
		} else if (ch == DOWN) {
			cursor_x++;
			if (cursor_x >= SIZE_X) cursor_x = SIZE_X - 1; //Clamp value
		} else if (ch == ERR) { //No keystroke
			; //Do nothing
		} else if (ch == '\n') {
			game_on = !game_on; //Pause or unpause the game
		}
		//else
		//mvprintw(SIZE_Y+5,0,"Unknown character: %i\n",ch);

		//Run the AI
		if (game_on) {
			for (Herb &h : herbs) {
				h.think();
			}
			for (Herbivore &h : herbivores) {
				h.think();
			}
			for (Carnivore &c : carnivores) {
				c.think();
			}
			//Clean up at most one corpse per frame, since the iterator goes invalid after erase
			//TODO: Fix this so it cleans up all corpses
			auto iter = herbivores.begin();
			while (iter != herbivores.end()) {
				if (iter->dead && iter->hunger <= -100) {
					world[index(iter->x, iter->y)] = OPEN;
					herbivores.erase(iter);
					break;
				}
				iter++;
			}
			auto iter2 = carnivores.begin();
			while (iter2 != carnivores.end()) {
				if (iter2->dead) {
					world[index(iter2->x, iter2->y)] = OPEN;
					carnivores.erase(iter2);
					break;
				}
				iter2++;
			}
		}

		//Redraw the screen
		clear();
		print_world();
		refresh();
	}
	clear();
	print_world();
	refresh();
	wait_ticks(300000);
	endwin(); // End curses mode
	system("clear");

	return 0;
}
