#pragma once

#include "node.hpp"
#include "color.hpp"

namespace libsdlpp {
	class box : public node {
	public:
		box(std::shared_ptr<node> parent, uint16_t width, uint16_t height, color bg) : 
			node(parent) {
			width_ = width;
			height_ = height;
			background_color_ = bg;
		}

		void on_render(sdl_renderer_ptr renderer) {

			SDL_SetRenderDrawColor(
				renderer.get(),
				background_color_.red, 
				background_color_.green, 
				background_color_.blue,
				background_color_.alpha);

			SDL_Rect r;
			r.x = x_;
			r.y = y_;
			r.w = width_;
			r.h = height_;

			SDL_RenderFillRect(renderer.get(), &r);
		}

	protected:
		color background_color_;
	};
}