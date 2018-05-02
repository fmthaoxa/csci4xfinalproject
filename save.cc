#include <iostream>
#include <string>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include "save.h"


void Save::hello() {
	std::cout<< "Hello world in save.cc" << std::endl;
}

bool file_exists(const std::string& filename) {
	struct stat buf;
	if (stat(filename.c_str(), &buf) != -1) {
		return true;
	}
	return false;

}


void Save::new_save(std::string name ) {


	std::ofstream file;
	file.open(name);
	file << name << std::endl;
	file << 0 << std::endl;
	file << 0 << std::endl;
	file << 0 << std::endl;
	file.close();


	std::cout << "this is the new save" << std::endl;


}


void Save::save(std::string name, int new_foo, int new_bar, int new_baz) {
	if(file_exists(name)) {
		std::ofstream file;
		file.open(name);
		file << name<< std::endl;
		file << new_foo << std::endl;
		file << new_bar << std::endl;
		file << new_baz << std::endl;
		file.close();
	}
	else {
		std::cout << "File does not exist\n";
	}
}
