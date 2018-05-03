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
	
	std::string newsave = "./savefolder/"+name;

	std::cout << name << std::endl;
	std::cout << newsave << std::endl;

	std::ofstream file;
	file.open(newsave);
	file << name << std::endl;
	file << 0 << std::endl;
	file << 0 << std::endl;
	file << 0 << std::endl;
	file.close();


	std::cout << "save.new_save ran." << std::endl;


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



void Save::print_save_files() {
	std::cout << "This is the list of save files" << std::endl;
	DIR *dpdf;
	struct dirent *epdf;

	dpdf = opendir("./savefolder/");

	if (dpdf !=NULL) {
		while (epdf = readdir(dpdf)) {
			std::cout << epdf->d_name << std:: endl;
		}
	}

	closedir(dpdf);

}


void Save::load_save(std::string save_file) {
	std::string file_loaded = "./savefolder/" + save_file;
	std::string line;
	std::ifstream file(file_loaded);

	if (file.is_open()) {
		while ( std::getline(file, line)) {
			std::cout << line;
		}
		file.close();
	}
	else {
		std::cout << "Cannot find file!" << std::endl;
	}

}












