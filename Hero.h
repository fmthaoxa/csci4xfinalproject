#include <iostream>
using namespace std;


class Hero {
	bool alive; //True if the Hero is alive
	int health; //Ranges from 0 to 100
	int attack;
	int x;
	int y;
	string name; //Name of the Hero
	public:
	bool get_alive()  {
		 return alive;
	}
	int get_health() {
		return health;
	}
	int get_attack()  {
		return attack;
	}
	string get_name()   {
		return name;
	}
	int get_x()   {
		return x;
	}
	int get_y()   {
		return y;
	}
	void set_alive(bool new_alive)  {
		alive = new_alive;
	}
	void set_health(int new_health) {
		health = new_health;
	}
	void set_attack(int new_attack)  {
		attack = new_attack;
	}
	void set_name(string name)      {
		this->name = name;
	}
	void set_x(int new_x)  {
		alive = new_x;
	}
	void set_y(int new_y)  {
		alive = new_y;
	}
	Hero() {
		alive = true;
		health = 100;
		attack = 10;
		int x;
		int y;
	}
	Hero(string new_name) {
		alive = true;
		health = 100;
		attack = 10;
		name = new_name;
		int x;
		int y;
	}
	Hero(bool new_alive, int new_health, int new_attack, string new_name, int x, int y) {
		alive = new_alive;
		health = new_health;
		attack = new_attack;
		name = new_name;
		x = new_x;
		y = new_y;
	}
	void damage(int danar, bool verbose = false) {
		if (!alive) return;
		health -= danar;
		if (health <= 0) alive = false;
		if (verbose) cout << name << "'s health is: " << health << endl;
	}
};
