#pragma once

#include "node.hpp"

namespace libsdlpp {
	class shape2d : public node {
	public:
		shape2d(std::shared_ptr<node> parent, position pos = position(0,0)) :
			node(parent) {
			set_pos(pos);
		}

		color background_color() const {
			return this->background_color_;
		}

		color border_color() const {
			return this->border_color_;
		}

		void show_border() {
			this->border_ = true;
		}

		void hide_border() {
			this->border_ = false;
		}

		void set_border_color(color c) {
			this->border_color_ = c;
		}

	protected:
		color background_color_;
		color border_color_;

		bool border_;
	};
}