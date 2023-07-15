#include <iostream>

#include "libsdlpp/window.hpp"
#include "libsdlpp/box2d.hpp"
#include "libsdlpp/triangle2d.hpp"
#include "libsdlpp/circle2d.hpp"

int main(int argc, char* argv[]) {

	using namespace libsdlpp;

	window w("Hello World", 800, 600);

	auto n = std::make_shared<node>(nullptr, position(100, 100));

	auto box = std::make_shared<box2d>(100, 100, position(100, 100), color::red());
	auto circle = std::make_shared<circle2d>(50, position(200, 100), color::red());
	auto triangle = std::make_shared<triangle2d>(100, 100, position(100, 100), color::red());
    box->show_border();
    box->set_border_color(color::black());

	n->add_child("box2d", box);
	n->add_child("circle2d", circle);
	n->add_child("triangle2d", triangle);
	

	w.init();
	w.set_child(n.get());
	w.run();

	return 1;
}