#include <iostream>

#include "libsdlpp/window.hpp"

int main(int argc, char* argv[]) {
	libsdlpp::window w("Hello World", 800, 600);

	w.init();

	w.run();

	std::cout << "Hello World" << std::endl;
	return 1;
}