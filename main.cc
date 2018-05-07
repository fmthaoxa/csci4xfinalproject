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
#include <string>
#include "save.h"
using namespace std;

class Monster;
class Key;
const unsigned char OPEN = ' '; //An open space
const unsigned char WALL = '#'; //A wall space; impassable
const unsigned char MONSTER = 'M'; //Eats herbivores
const unsigned char KEY = 'K';
const unsigned char PLAYER='P';
//Globals holding game state
int SIZE_X=40;
int SIZE_Y=40; //Dimensions of the world
int cursor_x, cursor_y; //Cursor for drawing stuff
unsigned char* world; //A character array holding our world
vector<Monster> monsters;
vector <Key> keys;
bool game_on; //Holds if the simulation is running
const int TIMEOUT=300;
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
class Key{
	public:
		Key (int new_x,int new_y) : x(new_x), y(new_y){}
		int x=0, y=0;
};
class Monster {
	public:
		Monster() {}
		Monster(int new_x, int new_y) : x(new_x), y(new_y) {}
		int x = 0, y = 0; //Location
		void think() { //AI For the monster
			int new_x = x + rand() % 3-1;
			int new_y = y + rand() % 3-1;
			if (world[index(new_x, new_y)] == OPEN) {
				world[index(new_x, new_y)] = MONSTER;
				world[index(x, y)] = OPEN;
				x = new_x;
				y = new_y;
			}
		}

};
int score=0;
bool key=false;
const int MONSTER_NUMBER = 1;
const int KEYS_PLZ=1;
//Builds an empty world with walls on the edges and open squares in the middle
void reset_world() {
	int count=0;
	for (int i = 0; i < SIZE_X; i++) {
		for (int j = 0; j < SIZE_Y; j++) {
			if (i == 0 || j == 0 || i == SIZE_X - 1 || j == SIZE_Y - 1) //Legacy code clean up if needed
				world[index(i, j)] = WALL;
			else
				world[index(i, j)] = OPEN;

			if (world[index( i,j)]==OPEN && rand() %140<KEYS_PLZ && count<1||world[index( i,j)]==OPEN && rand() %500<KEYS_PLZ && count<1&&i==SIZE_X-1&&j==SIZE_Y-1){
				world[index(i,j)] = KEY;
				keys.push_back(Key(i,j));
				count++;
			}
			if (world[index(i, j)] == OPEN && rand() % 750 < MONSTER_NUMBER) {
				world[index(i, j)] = MONSTER;
				monsters.push_back(Monster(i, j));
			}
		}
	}
	cout<<endl;
}


//Prints the entire world, bolding the square the cursor is on
void print_world() {
	for (int i = 0; i < SIZE_X; i++) {
		for (int j = 0; j < SIZE_Y; j++) {
			if (i == cursor_x && j == cursor_y){
					
				attron(A_UNDERLINE| A_BOLD);
			}
			int color = 1;
			if (world[index(i, j)] == WALL)
				color = 5;

			else if (world[index(i, j)] == KEY)
				color = 2;
			else if (world[index(i, j)] == MONSTER)
				color = 6;
			attron(COLOR_PAIR(color));
			mvaddch(i, j, world[index(i, j)]);
			attroff(COLOR_PAIR(color));
			attroff(A_UNDERLINE | A_BOLD);
		}
	}cout<<endl;
}

int main() {
	//Initialize random number generator
	srand(time(NULL));


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
	clear();
	world = new unsigned char[SIZE_X * SIZE_Y];
	reset_world();
	//MAIN LOOP
	int frame = 0;
	cursor_x = SIZE_X / 2, cursor_y = SIZE_Y / 2; //Cursor for drawing stuff
	game_on = true;
	while (true) {
		mvprintw(SIZE_X + 0, 0, "Score: %d", score);
		mvprintw(SIZE_X + 1, 0, "Type Q to quit");

		int ch = getch(); // Wait for user input, with TIMEOUT delay
		if (ch == 'q' || ch == 'Q') break;
		/*else if (ch == 'm' || ch == 'M') {
		  if (world[index(cursor_x, cursor_y)] == OPEN) {
		  world[index(cursor_x, cursor_y)] = MONSTER;
		  monsters.push_back(Monster(cursor_x, cursor_y));
		  }
		  }*/

		if(world[index(cursor_x, cursor_y)] == MONSTER){//kills the player
			mvprintw(SIZE_X + 2, 0, "You have been slain!");
			print_world();
			refresh();
			wait_ticks(300000);
			exit(1);
		}
		if(world[index(cursor_x, cursor_y)] == KEY){
			keys.pop_back();
			score++;
			reset_world();

		}
		//Handle arrow keys, the NCURSES #defs don't work here for some reason
		//KEY_UP, for example, is set to 0403 (259), not 65
		else if (ch == RIGHT) {
			cursor_y++;
			if (cursor_y >= SIZE_Y-1) cursor_y = SIZE_Y - 2; //Clamp value
		} else if (ch == LEFT) {
			cursor_y--;
			if (cursor_y < 1) cursor_y = 1;
		} else if (ch == UP) { //Should be KEY_UP, grr
			cursor_x--;
			if (cursor_x < 1) cursor_x = 1;
		} else if (ch == DOWN) {
			cursor_x++;
			if (cursor_x >= SIZE_X-1) cursor_x = SIZE_X - 2; //Clamp value
		} else if (ch == ERR) { //No keystroke
			; //Do nothing
		} else if (ch == '\n') {
			game_on = !game_on; //Pause or unpause the game
		}
		//else
		//mvprintw(SIZE_Y+5,0,"Unknown character: %i\n",ch);

		//Run the AI
		if (game_on) {
			for (Monster &c: monsters){	
				c.think();

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
	system("clear");

}

