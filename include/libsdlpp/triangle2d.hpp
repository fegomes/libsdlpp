#pragma once

#include "shape2d.hpp"
#include "color.hpp"

namespace libsdlpp {
	class triangle2d : public shape2d {
	public:
		triangle2d(std::shared_ptr<node> parent, uint16_t w, uint16_t h, color bg, position pos = position(0,0)) :
			shape2d(parent, pos) {
			set_size(w, h);
			background_color_ = bg;
		}

		void set_pos(position p) {
			shape2d::set_pos(p);
			update_positions();
		}

		void set_size(uint16_t w, uint16_t h) {
			shape2d::set_size(w, h);
			update_positions();
		}

		void update_positions() {
			top_.set_x((width_ / 2) + pos_.x());
			top_.set_y(pos_.y());

			left_.set_x(pos_.x());
			left_.set_y(height_ + pos_.y());

			right_.set_x(width_ + pos_.x());
			right_.set_y(height_ + pos_.y());
		}

		color background_color() const {
			return this->background_color_;
		}

		void on_render(sdl_renderer_ptr renderer) {

			SDL_SetRenderDrawColor(
				renderer.get(),
				background_color_.red,
				background_color_.green,
				background_color_.blue,
				background_color_.alpha);

			SDL_RenderDrawLine(renderer.get(), left_.x(), left_.y(), top_.x(), top_.y());
			SDL_RenderDrawLine(renderer.get(), top_.x(), top_.y(), right_.x(), right_.y());
			SDL_RenderDrawLine(renderer.get(), right_.x(), right_.y(), left_.x(), left_.y());

		}

	protected:
		color background_color_;

		position top_;
		position left_;
		position right_;
	};
}