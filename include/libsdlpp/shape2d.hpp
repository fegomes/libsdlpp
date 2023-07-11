#pragma once

#include "node.hpp"

namespace libsdlpp {
	class shape2d : public node {
	public:
		shape2d(std::shared_ptr<node> parent, position pos = position(0,0)) :
			node(parent) {
			set_pos(pos);
		}
	};
}