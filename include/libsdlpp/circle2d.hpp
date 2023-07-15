#pragma once

#include <chrono>

#include "shape2d.hpp"
#include "color.hpp"

namespace libsdlpp {
	class circle2d : public shape2d {
	public:
        circle2d(uint16_t radius, position pos = position(0, 0), color bc = color::black()) :
            shape2d(nullptr, pos, bc), radius_(radius) {
            pos_.set_x(pos_.x() + radius);
            pos_.set_y(pos_.y() + radius);
        }

		circle2d(std::shared_ptr<node> parent, uint16_t radius, position pos = position(0, 0), color bc = color::black()) :
			shape2d(parent, pos, bc), radius_(radius) {
			pos_.set_x(pos_.x() + parent->pos().x() + radius);
			pos_.set_y(pos_.y() + parent->pos().y() + radius);
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

				status += SDL_RenderDrawLine( renderer.get(), 
											  pos_.x() + parent()->pos().x() - offsety,
											  pos_.y() + parent()->pos().y() + offsetx, 
					                          pos_.x() + parent()->pos().x() + offsety, 
					                          pos_.y() + parent()->pos().y() + offsetx);

				status += SDL_RenderDrawLine( renderer.get(), 
											  pos_.x() + parent()->pos().x() - offsetx, 
                                              pos_.y() + parent()->pos().y() + offsety,
                                              pos_.x() + parent()->pos().x() + offsetx,
                                              pos_.y() + parent()->pos().y() + offsety);

				status += SDL_RenderDrawLine( renderer.get(), 
					                          pos_.x() + parent()->pos().x() - offsetx, 
					                          pos_.y() + parent()->pos().y() - offsety, 
					                          pos_.x() + parent()->pos().x() + offsetx, 
					                          pos_.y() + parent()->pos().y() - offsety);

				status += SDL_RenderDrawLine( renderer.get(), 
					                          pos_.x() + parent()->pos().x() - offsety, 
					                          pos_.y() + parent()->pos().y() - offsetx, 
					                          pos_.x() + parent()->pos().x() + offsety, 
					                          pos_.y() + parent()->pos().y() - offsetx);

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

			if (border_) {

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
					status += SDL_RenderDrawPoint(renderer.get(), pos_.x() + parent()->pos().x() + offsetx, pos_.y() + parent()->pos().y() + offsety);
					status += SDL_RenderDrawPoint(renderer.get(), pos_.x() + parent()->pos().x() + offsety, pos_.y() + parent()->pos().y() + offsetx);
					status += SDL_RenderDrawPoint(renderer.get(), pos_.x() + parent()->pos().x() - offsetx, pos_.y() + parent()->pos().y() + offsety);
					status += SDL_RenderDrawPoint(renderer.get(), pos_.x() + parent()->pos().x() - offsety, pos_.y() + parent()->pos().y() + offsetx);
					status += SDL_RenderDrawPoint(renderer.get(), pos_.x() + parent()->pos().x() + offsetx, pos_.y() + parent()->pos().y() - offsety);
					status += SDL_RenderDrawPoint(renderer.get(), pos_.x() + parent()->pos().x() + offsety, pos_.y() + parent()->pos().y() - offsetx);
					status += SDL_RenderDrawPoint(renderer.get(), pos_.x() + parent()->pos().x() - offsetx, pos_.y() + parent()->pos().y() - offsety);
					status += SDL_RenderDrawPoint(renderer.get(), pos_.x() + parent()->pos().x() - offsety, pos_.y() + parent()->pos().y() - offsetx);

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

		}

	protected:
		uint16_t radius_;
	};
}