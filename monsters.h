#include <string>

class Monster {
		std::string name = "Monster";
		int x = 0;
		int y = 0;
		bool alive = true;
		int health = 50;
		int attack = 0;
			
	public: 

		Monster() {}
		
		std::string get_name() 	{ return name;   }
		int get_x() 			{ return x;      }
		int get_y() 			{ return y;      }
		bool get_alive()		{ return alive;  }
		int get_health() 		{ return health; }
		int get_attack() 		{ return attack; }
		
		void set_name (std::string new_name) { name = new_name; 	}
		void set_x (int new_x) 				 { x = new_x; 			}
		void set_y (int new_y)               { y = new_y;			}
		void set_alive (bool new_alive)      { alive = new_alive;   }
		void set_health (int new_health) 	 { health = new_health; }
	
/*		void damage (int danar, bool verbose = false) {
			if (!alive) return;
			health -= danar;
			if (health <= 0) alive = false;
			if (verbose) cout << name << "'s health is: " << health << ".\n";
		}
*/
};


//These are here in case we decide to use inheritance
class Boss : public Monster {
	public:
		int attack = 15;
};
