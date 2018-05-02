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

};

#endif
