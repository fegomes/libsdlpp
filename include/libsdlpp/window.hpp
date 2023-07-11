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
		window() : id_(-1), title_(""), width_(100), height_(100), running_(true), child_(nullptr), event_() {}

		window(const std::string& title, uint16_t width, uint16_t height) :
			id_(-1), title_(title), width_(width), height_(height), running_(true), child_(nullptr), event_() {
		}

		~window() {
			SDL_StopTextInput();

			TTF_Quit();
			IMG_Quit();

			SDL_QuitSubSystem(SDL_INIT_AUDIO);

			if (window_) {
				window_.release();
			}
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
				background_color_.red_, 
				background_color_.green_,
				background_color_.blue_,
				background_color_.alpha_);

			SDL_RenderClear(renderer_.get());

			if (child_) {
				child_->render(renderer_);
			}

			SDL_RenderPresent(renderer_.get());
		}

		void set_background_color(color bc) {
			background_color_ = bc;
		}

		void set_title(const std::string t) {
			this->title_ = t;
			SDL_SetWindowTitle(window_.get(), title_.c_str());
		}

		void set_height(const uint32_t h) {
			assert(h >= 0);
			this->height_ = h;
			SDL_SetWindowSize(window_.get(), width_, height_);
		}

		void set_width(const uint32_t w) {
			assert(w >= 0);
			this->width_ = w;
			SDL_SetWindowSize(window_.get(), width_, height_);
		}

		void set_child(node* child) {
			assert(child != nullptr);
			this->child_.reset(child);
		}

		void quit() {
			this->running_ = false;
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

		std::unique_ptr<node> child_;
	};
}