#include <iostream>

#include "libsdlpp/window.hpp"
#include "libsdlpp/box2d.hpp"
#include "libsdlpp/triangle2d.hpp"
#include "libsdlpp/circle2d.hpp"

int main(int argc, char* argv[]) {

	using namespace libsdlpp;

	window w("Hello World", 800, 600);

	auto b = std::make_unique<box2d>(nullptr, 100,100, position(100, 100), color::green(), color::red());

	w.init();
	w.set_child(b.release());
	w.run();

	return 1;
}