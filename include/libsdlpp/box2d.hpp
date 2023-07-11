#pragma once

#include "shape2d.hpp"
#include "color.hpp"

namespace libsdlpp {
	class box2d : public shape2d {
	public:
		box2d(std::shared_ptr<node> parent, uint16_t w, uint16_t h, position pos = position(0, 0), color border = color::black(), color background = color::white()) :
			shape2d(parent, pos) {
			set_size(w, h);
			border_color_ = border;
			background_color_ = background;
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

			SDL_SetRenderDrawColor(
				renderer.get(),
				border_color_.red_,
				border_color_.green_,
				border_color_.blue_,
				border_color_.alpha_);

			SDL_RenderDrawLine(renderer.get(), pos_.x(), pos_.y(), pos_.x(), width_ + pos_.x());
			SDL_RenderDrawLine(renderer.get(), pos_.x(), width_ + pos_.x(), height_ + pos_.y(), width_ + pos_.x());
			SDL_RenderDrawLine(renderer.get(), height_ + pos_.y(), width_ + pos_.x(), height_ + pos_.y(), pos_.y());
			SDL_RenderDrawLine(renderer.get(), height_ + pos_.y(), pos_.y(), pos_.x(), pos_.y());
		}

	protected:
		color background_color_;
		color border_color_;
	};
}