#pragma once

#include "node.hpp"

namespace libsdlpp {
	class shape2d : public node {
	public:
		shape2d(std::shared_ptr<node> parent, position pos = position(0,0)) :
			node(parent), border_(false) {
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

		void set_background_color(color c) {
			this->background_color_ = c;
		}

		void set_border_color(color c) {
			this->border_color_ = c;
		}

	protected:
		virtual void on_render(sdl_renderer_ptr renderer) = 0;

	protected:
		color background_color_;
		color border_color_;

		bool border_;
	};
}