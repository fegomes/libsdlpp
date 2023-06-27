#include <iostream>

#include "libsdlpp/window.hpp"
#include "libsdlpp/box.hpp"

int main(int argc, char* argv[]) {

	libsdlpp::window w("Hello World", 800, 600);

	auto b = std::make_unique<libsdlpp::box>(nullptr, 100,100, libsdlpp::color(0,0,0,255));

	w.init();
	w.set_child(b.release());
	w.run();

	return 1;
}