#pragma once

#include <chrono>

#include "shape2d.hpp"
#include "color.hpp"

namespace libsdlpp {
	class triangle2d : public shape2d {
	public:
        triangle2d(uint16_t w, uint16_t h, position pos = position(0, 0), color bc = color::black()) :
            shape2d(nullptr, pos, bc) {
            set_size(w, h);
            ignore_events();
            update_positions();
        }

		triangle2d(std::shared_ptr<node> parent, uint16_t w, uint16_t h, position pos = position(0, 0), color bc = color::black()) :
			shape2d(parent, pos, bc) {
			set_size(w, h);
			ignore_events();
			update_positions();
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
			top_.set_x(((width_ / 2) + pos_.x()) + parent()->pos().x());
			top_.set_y(pos_.y() + parent()->pos().x());

			left_.set_x(pos_.x() + parent()->pos().x());
			left_.set_y(height_ + pos_.y() + parent()->pos().y());

			right_.set_x(width_ + pos_.x() + parent()->pos().x());
			right_.set_y(height_ + pos_.y() + parent()->pos().x());
		}

		void on_render(sdl_renderer_ptr renderer) {

			SDL_FPoint p;
			p.x = parent()->pos().x();
			p.y = parent()->pos().y();

			const std::vector<SDL_Vertex> verts = {
				{ top_.to_fpoint(), background_color_.to_sdl(), p },
				{ left_.to_fpoint(), background_color_.to_sdl(), p },
				{ right_.to_fpoint(), background_color_.to_sdl(), p },
			};

			SDL_RenderGeometry(renderer.get(), nullptr, verts.data(), (int) verts.size(), nullptr, 0);

			if (border_) {
				SDL_SetRenderDrawColor(
					renderer.get(),
					border_color_.red_,
					border_color_.green_,
					border_color_.blue_,
					border_color_.alpha_);

				SDL_RenderDrawLine(renderer.get(), left_.x() + parent()->pos().x(), left_.y() + parent()->pos().y(), top_.x() + parent()->pos().x(), top_.y() + parent()->pos().y());
				SDL_RenderDrawLine(renderer.get(), top_.x() + parent()->pos().x(), top_.y() + parent()->pos().y(), right_.x() + parent()->pos().x(), right_.y() + parent()->pos().y());
				SDL_RenderDrawLine(renderer.get(), right_.x() + parent()->pos().x(), right_.y() + parent()->pos().y(), left_.x() + parent()->pos().x(), left_.y() + parent()->pos().y());
			}
		}

	protected:
		position top_;
		position left_;
		position right_;
	};
}