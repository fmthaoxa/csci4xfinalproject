#ifndef SAVE_H
#define SAVE_H
class Save {
	private:
		int foo;
		int bar;
		int baz;
		
	public:
		void hello();
		
		void save(std::string name, int new_foo, int new_bar, int new_baz);

		void new_save(std::string new_name);

		void print_save_files();
		
		void load_save(std::string save_file);
};

#endif
