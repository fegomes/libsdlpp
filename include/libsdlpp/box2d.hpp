#pragma once

#include "shape2d.hpp"
#include "color.hpp"

namespace libsdlpp {
	class box2d : public shape2d {
	public:
		box2d(std::shared_ptr<node> parent, uint16_t w, uint16_t h, color bg, position pos = position(0, 0)) :
			shape2d(parent, pos) {
			set_size(w, h);
			background_color_ = bg;
		}

		color background_color() const {
			return this->background_color_;
		}

		void on_render(sdl_renderer_ptr renderer) {

			SDL_SetRenderDrawColor(
				renderer.get(),
				background_color_.red_,
				background_color_.green_,
				background_color_.blue_,
				background_color_.alpha_);

			SDL_Rect r;
			r.x = pos_.x();
			r.y = pos_.y();
			r.w = width_;
			r.h = height_;

			SDL_RenderFillRect(renderer.get(), &r);
		}

	protected:
		color background_color_;
	};
}