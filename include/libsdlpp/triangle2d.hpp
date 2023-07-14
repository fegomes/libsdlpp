#pragma once

#include <chrono>

#include "shape2d.hpp"
#include "color.hpp"

namespace libsdlpp {
	class triangle2d : public shape2d {
	public:
		triangle2d(std::shared_ptr<node> parent, uint16_t w, uint16_t h, position pos = position(0, 0), color bc = color::black()) :
			shape2d(parent, pos) {
			set_size(w, h);
			set_border_color(color::white());
			set_background_color(bc);
			ignore_events();
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

		void on_render(sdl_renderer_ptr renderer) {

			const std::vector<SDL_Vertex> verts = {
				{ top_.to_fpoint(), background_color_.to_sdl(), SDL_FPoint{ 0 }, },
				{ left_.to_fpoint(), background_color_.to_sdl(), SDL_FPoint{ 0 }, },
				{ right_.to_fpoint(), background_color_.to_sdl(), SDL_FPoint{ 0 }, },
			};

			SDL_RenderGeometry(renderer.get(), nullptr, verts.data(), (int) verts.size(), nullptr, 0);

			if (border_) {
				SDL_SetRenderDrawColor(
					renderer.get(),
					border_color_.red_,
					border_color_.green_,
					border_color_.blue_,
					border_color_.alpha_);

				SDL_RenderDrawLine(renderer.get(), left_.x(), left_.y(), top_.x(), top_.y());
				SDL_RenderDrawLine(renderer.get(), top_.x(), top_.y(), right_.x(), right_.y());
				SDL_RenderDrawLine(renderer.get(), right_.x(), right_.y(), left_.x(), left_.y());
			}
		}

	protected:
		position top_;
		position left_;
		position right_;
	};
}