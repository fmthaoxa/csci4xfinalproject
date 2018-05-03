#include <iostream>
#include <string>
#include "save.h"
using namespace std;


int main () {
	string name;
	Save save;

	save.hello();

	save.new_save("Aaron");
	save.new_save("John");
	save.new_save("Batman");

	save.print_save_files();
	
	save.load_save("cat");
	save.load_save("Batman");
	/*
	while(true) {
		cout << "Enter a name to save" << endl;
		cin >> name;
		save.save(name,1,2,3);
	}
	*/
}
