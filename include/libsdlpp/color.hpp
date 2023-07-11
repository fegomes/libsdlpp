#pragma once

namespace libsdlpp {
	class color {
	public:
		color() :
			red(g_red), green(g_green), blue(g_blue), alpha(g_alpha) {
		}

		color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) :
			red(r), green(g), blue(b), alpha(a) {
		}

	public:
		uint8_t red;
		uint8_t green;
		uint8_t blue;
		uint8_t alpha;

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