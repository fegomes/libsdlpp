#pragma once
#include <cassert>
#include <memory>
#include <vector>
#include <future>

#include "position.hpp"
#include "color.hpp"
#include "renderer.hpp"

namespace libsdlpp {
	class node {
	public:
		node(std::shared_ptr<node> parent) : 
			parent_(parent), visible_(true), handle_events_(true), pos_(0,0), width_(0), height_(0) {
		}

		~node() { 
			this->childs_.clear();
		}

		position pos() const {
			return this->pos_;
		}

		uint16_t width() const {
			return this->width_;
		}

		uint16_t height() const {
			return this->height_;
		}

		virtual void set_pos(position p) {
			pos_ = p;
		}

		virtual void set_size(uint16_t w, uint16_t h) {
			set_width(w);
			set_height(h);
		}

		virtual void set_x(uint16_t x) {
			pos_.set_x(x);
		}

		virtual void set_y(uint16_t y) {
			pos_.set_y(y);
		}

		virtual void set_width(uint16_t w) {
			assert(w >= 0);
			this->width_ = w;
		}

		virtual void set_height(uint16_t h) {
			assert(h >= 0);
			this->height_ = h;
		}

		bool visible() const {
			return this->visible_;
		}

		void hide() {
			this->visible_ = false;
		}

		void show() {
			this->visible_ = true;
		}

		void ignore_events() {
			handle_events_ = false;
		}
		
		void accept_events() {
			handle_events_ = true;
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

		void handle_event(const SDL_Event& e) {
			if (handle_events_) {
				on_handle_event(e);

				for (auto ci = childs_.begin(); ci != childs_.end(); ci++) {
					(*ci)->on_handle_event(e);
				}
			}
		}

		void async_handle_event(const SDL_Event& e) {
			if (handle_events_) {
				std::future<void> discart = std::async(std::launch::async, std::bind(&node::on_async_handle_event, this, std::placeholders::_1), e);

				for (auto ci = childs_.begin(); ci != childs_.end(); ci++) {
					discart = std::async(std::launch::async, std::bind(&node::on_async_handle_event, (*ci), std::placeholders::_1), e);
				}
			}
		}

	protected:
		virtual void on_handle_event(const SDL_Event& e) {}
		virtual void on_async_handle_event(const SDL_Event& e) {}
		virtual void on_render(sdl_renderer_ptr renderer) {};

	protected:
		std::shared_ptr<node> parent_;

		bool visible_;
		bool handle_events_;

		position pos_;

		uint16_t width_;
		uint16_t height_;

		std::vector<std::shared_ptr<node>> childs_;
	};
}
