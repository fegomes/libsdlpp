#pragma once

#include <memory>
#include <string>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "color.hpp"
#include "renderer.hpp"
#include "node.hpp"

#define TTF_INIT_FAILED -1
#define IMG_INIT_FAILED 0

namespace libsdlpp {

	struct SDLWindowDestroyer {
		void operator()(SDL_Window* w) const {
			SDL_DestroyWindow(w);
		}
	};

	typedef std::unique_ptr<SDL_Window, SDLWindowDestroyer> sdl_window;
	typedef std::shared_ptr<SDL_Window> sdl_window_ptr;

	class window {

	public:
		window() : title_(""), width_(100), height_(100), running_(true) {}

		window(const std::string& title, uint16_t width, uint16_t height) :
			title_(title), width_(width), height_(height), running_(true) {}

		~window() {
			SDL_StopTextInput();

			window_.release();
		}

	public:
		bool init() {

			if (SDL_Init(SDL_INIT_EVERYTHING)) {
				std::cerr << "could not initialize SDL_INIT_EVERYTHING : " << SDL_GetError() << std::endl;
				return false;
			}

			if (TTF_INIT_FAILED == TTF_Init()) {
				std::cerr << "could not initialize TTF_Init: " << TTF_GetError() << std::endl;
				return false;
			}

			if (IMG_INIT_FAILED == IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
				std::cerr << "could not initialize IMG_Init: " << IMG_GetError() << std::endl;
				return false;
			}

			window_.reset(SDL_CreateWindow(
				title_.c_str(),
				SDL_WINDOWPOS_UNDEFINED_DISPLAY(0),
				SDL_WINDOWPOS_UNDEFINED_DISPLAY(0),
				width_, 
				height_,
				SDL_WINDOW_SHOWN
			));

			if (!window_) {
				std::cerr << "could not create window: " << SDL_GetError() << std::endl;
				return false;
			}

			id_ = SDL_GetWindowID(window_.get());

			renderer_.reset(SDL_CreateRenderer(window_.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC), SDL_DestroyRenderer);

			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
			SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");
			SDL_SetHint(SDL_HINT_ALLOW_TOPMOST, "1");

			SDL_StartTextInput();

			return true;
		}

		bool poll_event() {

			if (SDL_PollEvent(&event_) != 0) {
				return handle_event(&event_);
			}

			return true;
		}

		bool handle_event(SDL_Event* e) {

			if (e->type == SDL_QUIT) {
				return false;
			}

			return true;
		}

		void run() {
			while (running_) {
				running_ = poll_event();
				render();
			}
		}

		void render() {
			SDL_SetRenderDrawColor(
				renderer_.get(), 
				background_color_.red, 
				background_color_.green,
				background_color_.blue,
				background_color_.alpha);

			SDL_RenderClear(renderer_.get());

			for (auto ci = childs_.begin(); ci != childs_.end(); ci++) {
				(*ci).render(renderer_);
			}

			SDL_RenderPresent(renderer_.get());
		}

		void set_background_color(color c) {
			background_color_ = c;
		}

		void set_title(const std::string title) {
			title_ = title;
			SDL_SetWindowTitle(window_.get(), title_.c_str());
		}

		void set_height(const uint32_t height) {
			height_ = height;
			SDL_SetWindowSize(window_.get(), width_, height_);
		}

		void set_width(const uint32_t width) {
			width_ = width;
			SDL_SetWindowSize(window_.get(), width_, height_);
		}

		void quit() {
			running_ = false;
		}

	protected:
		sdl_window window_;
		sdl_renderer_ptr renderer_;

		SDL_Event event_;

	protected:
		uint32_t id_;

		std::string title_;

		uint16_t width_;
		uint16_t height_;

		color background_color_;

		bool running_;

		std::vector<node> childs_;
	};
}