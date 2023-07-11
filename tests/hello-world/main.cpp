#include <iostream>

#include "libsdlpp/window.hpp"
#include "libsdlpp/box2d.hpp"
#include "libsdlpp/triangle2d.hpp"

int main(int argc, char* argv[]) {

	using namespace libsdlpp;

	window w("Hello World", 800, 600);

	auto b = std::make_unique<triangle2d>(nullptr, 100, 100, color::red(), color::blue(), position(100,100));

	w.init();
	w.set_child(b.release());
	w.run();

	return 1;
}