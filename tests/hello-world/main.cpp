#include <iostream>

#include "libsdlpp/window.hpp"
#include "libsdlpp/line2d.hpp"
#include "libsdlpp/box2d.hpp"
#include "libsdlpp/triangle2d.hpp"
#include "libsdlpp/circle2d.hpp"

int main(int argc, char* argv[]) {

	using namespace libsdlpp;

	window w("Hello World", 1280, 800);

	auto n = std::make_shared<node>(nullptr, position(100, 100));

	auto line = std::make_shared<line2d>(position(0, 0), position(100,300), color::black());
	auto box = std::make_shared<box2d>(100, 100, position(0, 0), color::red());
	auto circle = std::make_shared<circle2d>(50, position(100, 0), color::red());
	auto triangle = std::make_shared<triangle2d>(100, 100, position(200, 0), color::red());
	auto triangle2 = std::make_shared<triangle2d>(100, 100, position(200, 0), color::red());

	n->add_child("line", line);
	n->add_child("box2d", box);
	n->add_child("circle2d", circle);
	n->add_child("triangle2d", triangle);
	n->add_child("triangle2d2", triangle2);

	w.init();
	w.set_child(n.get());
	w.run();

	return 1;
}