#pragma once

#include <chrono>

#include "shape2d.hpp"
#include "color.hpp"

namespace libsdlpp {
	class circle2d : public shape2d {
	public:
		circle2d(std::shared_ptr<node> parent, uint16_t radius, position pos = position(0, 0), color border = color::black(), color background = color::white()) :
			shape2d(parent, pos), radius_(radius) {
			border_color_ = border;
			background_color_ = background;
			pos_.set_x(pos_.x() + radius);
			pos_.set_y(pos_.y() + radius);
		}

		color background_color() const {
			return this->background_color_;
		}
		
		color border_color() const {
			return this->border_color_;
		}

		void on_render(sdl_renderer_ptr renderer) {

			int offsetx, offsety, d;
			int status;

			SDL_SetRenderDrawColor(
				renderer.get(),
				background_color_.red_,
				background_color_.green_,
				background_color_.blue_,
				background_color_.alpha_);

			offsetx = 0;
			offsety = radius_;
			d = radius_ - 1;
			status = 0;

			while (offsety >= offsetx) {

				status += SDL_RenderDrawLine(renderer.get(), pos_.x() - offsety, pos_.y() + offsetx, pos_.x() + offsety, pos_.y() + offsetx);
				status += SDL_RenderDrawLine(renderer.get(), pos_.x() - offsetx, pos_.y() + offsety, pos_.x() + offsetx, pos_.y() + offsety);
				status += SDL_RenderDrawLine(renderer.get(), pos_.x() - offsetx, pos_.y() - offsety, pos_.x() + offsetx, pos_.y() - offsety);
				status += SDL_RenderDrawLine(renderer.get(), pos_.x() - offsety, pos_.y() - offsetx, pos_.x() + offsety, pos_.y() - offsetx);

				if (status < 0) {
					status = -1;
					break;
				}

				if (d >= 2 * offsetx) {
					d -= 2 * offsetx + 1;
					offsetx += 1;
				}
				else if (d < 2 * (radius_ - offsety)) {
					d += 2 * offsety - 1;
					offsety -= 1;
				}
				else {
					d += 2 * (offsety - offsetx - 1);
					offsety -= 1;
					offsetx += 1;
				}
			}

			SDL_SetRenderDrawColor(
				renderer.get(),
				border_color_.red_,
				border_color_.green_,
				border_color_.blue_,
				border_color_.alpha_);

			offsetx = 0;
			offsety = radius_;
			d = radius_ - 1;
			status = 0;

			while (offsety >= offsetx) {
				status += SDL_RenderDrawPoint(renderer.get(), pos_.x() + offsetx, pos_.y() + offsety);
				status += SDL_RenderDrawPoint(renderer.get(), pos_.x() + offsety, pos_.y() + offsetx);
				status += SDL_RenderDrawPoint(renderer.get(), pos_.x() - offsetx, pos_.y() + offsety);
				status += SDL_RenderDrawPoint(renderer.get(), pos_.x() - offsety, pos_.y() + offsetx);
				status += SDL_RenderDrawPoint(renderer.get(), pos_.x() + offsetx, pos_.y() - offsety);
				status += SDL_RenderDrawPoint(renderer.get(), pos_.x() + offsety, pos_.y() - offsetx);
				status += SDL_RenderDrawPoint(renderer.get(), pos_.x() - offsetx, pos_.y() - offsety);
				status += SDL_RenderDrawPoint(renderer.get(), pos_.x() - offsety, pos_.y() - offsetx);

				if (status < 0) {
					status = -1;
					break;
				}

				if (d >= 2 * offsetx) {
					d -= 2 * offsetx + 1;
					offsetx += 1;
				}
				else if (d < 2 * (radius_ - offsety)) {
					d += 2 * offsety - 1;
					offsety -= 1;
				}
				else {
					d += 2 * (offsety - offsetx - 1);
					offsety -= 1;
					offsetx += 1;
				}
			}

		}

	protected:
		color background_color_;
		color border_color_;

		uint16_t radius_;

		std::vector<SDL_Vertex> verts_;
	};
}