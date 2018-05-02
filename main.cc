#include <iostream>
#include <string>
#include "save.h"
using namespace std;


int main () {
	string name;
	Save save;

	save.hello();

	save.new_save("Aaron");

	while(true) {
		cout << "Enter a name to save" << endl;
		cin >> name;
		save.save(name,1,2,3);
	}
}
