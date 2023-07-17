#pragma once

#include "shape2d.hpp"
#include "color.hpp"

namespace libsdlpp {
	class box2d : public shape2d {
	public:
        box2d(uint16_t w, uint16_t h, position pos = position(0, 0), color bc = color::black()) :
            shape2d(nullptr, pos, bc) {
            set_size(w, h);
        }

		box2d(std::shared_ptr<node> parent, uint16_t w, uint16_t h, position pos = position(0, 0), color bc = color::black()) :
			shape2d(parent, pos, bc) {
			set_size(w, h);
		}

		void repos() {}

		void on_render(sdl_renderer_ptr renderer) {

			SDL_SetRenderDrawColor(
				renderer.get(),
				background_color_.red_,
				background_color_.green_,
				background_color_.blue_,
				background_color_.alpha_);

			SDL_Rect r;
			r.x = pos_.x() + parent()->pos().x();
			r.y = pos_.y() + parent()->pos().y();
			r.w = width_;
			r.h = height_;

			SDL_RenderFillRect(renderer.get(), &r);

			if(border_) {
				SDL_SetRenderDrawColor(
					renderer.get(),
					border_color_.red_,
					border_color_.green_,
					border_color_.blue_,
					border_color_.alpha_);

				// border left
				SDL_RenderDrawLine(	renderer.get(), 
									pos_.x() + parent()->pos().x(), 
									pos_.y() + parent()->pos().y(), 
									pos_.x() + parent()->pos().x(), 
									pos_.y() + parent()->pos().y() + height_);

				// border bottom
				SDL_RenderDrawLine(	renderer.get(), 
									pos_.x() + parent()->pos().x(), 
									pos_.y() + parent()->pos().y() + height_, 
									pos_.x() + parent()->pos().x() + width_, 
									pos_.y() + parent()->pos().y() + height_);
				
				// border right
				SDL_RenderDrawLine(	renderer.get(), 
									pos_.x() + parent()->pos().x() + width_, 
									pos_.y() + parent()->pos().y() + height_, 
									pos_.x() + parent()->pos().x() + width_, 
									pos_.y() + parent()->pos().y());
				
				// border top
				SDL_RenderDrawLine(	renderer.get(), 
									pos_.x() + parent()->pos().x() + width_,
									pos_.y() + parent()->pos().y(),
									pos_.x() + parent()->pos().x(), pos_.y() + parent()->pos().y());
			}
		}

	};
}