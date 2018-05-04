#ifndef FOO_H
#define FOO_H

class Foo {
	private:
		std::string name = "DEFUALT";
		int a = 100;
		int b = 100;
		int c = 100;
	public:
		void set_name(std::string new_name){
			name = new_name;
		}
		void set_a(int new_a) {
			a = new_a;
		}
		void set_b(int new_b) {
			b = new_b;
		}
		void set_c(int new_c) {
			c = new_c;
		}

		void print() {
			std::cout << "Here are the new outputs\n" << std::endl;
			std::cout << name << std::endl;
			std::cout << a << std::endl;
			std::cout << b << std::endl;
			std::cout << c << std::endl;
		}


};
#endif
