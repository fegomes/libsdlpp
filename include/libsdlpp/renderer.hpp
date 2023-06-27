#pragma once
#include <memory>

namespace libsdlpp {

	struct SDLRenderedDestroyer {
		void operator()(SDL_Renderer* r) const {
			SDL_DestroyRenderer(r);
		}
	};

	typedef std::unique_ptr<SDL_Renderer, SDLRenderedDestroyer> sdl_renderer;
	typedef std::shared_ptr<SDL_Renderer> sdl_renderer_ptr;
}