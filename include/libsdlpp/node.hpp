#pragma once
#include <memory>
#include <vector>

#include "color.hpp"
#include "renderer.hpp"

namespace libsdlpp {
	class node {
	public:
		node(std::shared_ptr<node> parent) : parent_(parent), visible_(true), x_(0), y_(0), width_(0), height_(0) {}

		~node(){
			childs_.clear();
		}

		uint16_t x() const {
			return x_;
		}

		uint16_t y() const {
			return y_;
		}

		uint16_t width() const {
			return width_;
		}

		uint16_t height() const {
			return height_;
		}

		bool visible() const {
			return visible_;
		}

		void render(sdl_renderer_ptr renderer) {
			if (visible()) {

				on_render(renderer);

				for (auto ci = childs_.begin(); ci != childs_.end(); ci++) {
					if (visible()) {
						(*ci)->on_render(renderer);
					}
				}
			}
		}

		virtual void on_render(sdl_renderer_ptr renderer) = 0;

	protected:
		std::shared_ptr<node> parent_;

		bool visible_;

		uint16_t x_;
		uint16_t y_;

		uint16_t width_;
		uint16_t height_;

		std::vector<std::shared_ptr<node>> childs_;
	};
}
