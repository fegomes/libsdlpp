#include <iostream>

#include "libsdlpp/window.hpp"

int main(int argc, char* argv[]) {
	libsdlpp::window w;
	

	w.init();

	w.run();

	std::cout << "Hello World" << std::endl;
	return 1;
}