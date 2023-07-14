#include <iostream>

#include "libsdlpp/window.hpp"
#include "libsdlpp/box2d.hpp"
#include "libsdlpp/triangle2d.hpp"
#include "libsdlpp/circle2d.hpp"

int main(int argc, char* argv[]) {

	using namespace libsdlpp;

	window w("Hello World", 800, 600);

	auto box = std::make_unique<triangle2d>(nullptr, 100, 100 , position(100, 100), color::red());
	
	box->show_border();
	box->set_border_color(color::black());

	w.init();
	w.set_child(box.release());
	w.run();

	return 1;
}