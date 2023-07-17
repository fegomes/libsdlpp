#pragma once

#include "node.hpp"

namespace libsdlpp {
	class shape2d : public node {
	public:

        shape2d(position pos = position(0, 0), color bc = color::black()) :
            node(nullptr, pos), border_(false) {
            set_border_color(color::white());
            set_background_color(bc);
            ignore_events();
        }

		shape2d(std::shared_ptr<node> parent, position pos = position(0,0), color bc = color::black()) :
			node(parent, pos), border_(false) {
			set_border_color(color::white());
			set_background_color(bc);
			ignore_events();
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

		virtual void repos() = 0;

	protected:
		virtual void on_render(sdl_renderer_ptr renderer) = 0;

	private:
		void handle_event(const SDL_Event& e) {};
		void async_handle_event(const SDL_Event& e) {};

	protected:
		color background_color_;
		color border_color_;

		bool border_;
	};
}