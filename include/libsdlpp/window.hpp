#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

namespace libsdlpp {
	class window {
	public:
		window() {

		}

	public:
		bool init() {
			if (SDL_Init(0) < 0) {
				fprintf(stderr, "could not initialize SDL_Init: %s\n", SDL_GetError());
				return false;
			}

			if (SDL_InitSubSystem(SDL_INIT_VIDEO)) {
				fprintf(stderr, "could not initialize SDL_INIT_VIDEO: %s\n", SDL_GetError());
				return false;
			}

			if (SDL_InitSubSystem(SDL_INIT_AUDIO)) {
				fprintf(stderr, "could not initialize SDL_INIT_AUDIO: %s\n", SDL_GetError());
				return false;
			}

			TTF_Init();
			IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

			_window = SDL_CreateWindow(
				"title",
				SDL_WINDOWPOS_UNDEFINED_DISPLAY(0), SDL_WINDOWPOS_UNDEFINED_DISPLAY(0),
				800, 600,
				SDL_WINDOW_SHOWN
			);

			if (_window == NULL) {
				fprintf(stderr, "could not create window: %s\n", SDL_GetError());
				return false;
			}

			SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
			SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");
			SDL_SetHint(SDL_HINT_ALLOW_TOPMOST, "1");
			SDL_StartTextInput();

			int id = SDL_GetWindowID(_window);

			return true;
		}

		bool poll_event() {

			SDL_Event e;
			if (SDL_PollEvent(&e) != 0)
			{
				return handle_event(&e);
			}

			return true;
		}

		bool handle_event(SDL_Event* e) {

			if (e->type == SDL_QUIT)
			{
				return false;
			}

			return true;
		}

		void run() {

			bool running = true;

			while (running)
			{
				if (!poll_event()) {
					running = false;
				}

				render();
			}
		}

		bool render() {
			SDL_SetRenderDrawColor(_render, 255, 255, 255, 255);
			SDL_RenderClear(_render);


			SDL_RenderPresent(_render);
			return true;
		}

	private:
		SDL_Window* _window = nullptr;
		SDL_Renderer* _render = nullptr;
	};
}