#pragma once
#include <cassert>

#include <SDL_rect.h>

namespace libsdlpp {
	class position {
	public:
		position() {
			set_x(0);
			set_y(0);
		}

		position(uint16_t x, uint16_t y) {
			set_x(x);
			set_y(y);
		}

		position(const position& pos) {
			set_x(pos.x());
			set_y(pos.y());
		}

		void set_x(uint16_t x) {
			assert(x >= 0);
			this->x_ = x;
		}

		void set_y(uint16_t y) {
			assert(y >= 0);
			this->y_ = y;
		}

		uint16_t x() const {
			return this->x_;
		}

		uint16_t y() const {
			return this->y_;
		}

		SDL_FPoint to_fpoint() const {
			return SDL_FPoint{ (float) x_, (float) y_ };
		}

		SDL_Point to_point() const {
			return SDL_Point{ (int) x_, (int) y_ };
		}

	public:
		uint16_t x_;
		uint16_t y_;
	};
}
