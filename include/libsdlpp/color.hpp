#pragma once

namespace libsdlpp {
	class color {
	public:
		color() :
			red_(g_red), green_(g_green), blue_(g_blue), alpha_(g_alpha) {
		}

		color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) :
			red_(r), green_(g), blue_(b), alpha_(a) {
		}

		SDL_Color to_sdl() const {
			return SDL_Color{ red_, green_, blue_, alpha_ };
		}

		static color red() {
			return color(255, 0, 0, 255);
		}

		static color green() {
			return color(0, 255, 0, 255);
		}

		static color blue() {
			return color(0, 0, 255, 255);
		}

		static color white() {
			return color(255, 255, 255, 255);
		}

		static color black() {
			return color(0, 0, 0, 255);
		}

	public:
		uint8_t red_;
		uint8_t green_;
		uint8_t blue_;
		uint8_t alpha_;

	public:
		static uint8_t g_red;
		static uint8_t g_green;
		static uint8_t g_blue;
		static uint8_t g_alpha;
	};

	uint8_t color::g_red = 255;
	uint8_t color::g_green = 255;
	uint8_t color::g_blue = 255;
	uint8_t color::g_alpha = 255;
}