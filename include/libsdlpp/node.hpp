#pragma once
#include <cassert>
#include <memory>
#include <map>
#include <future>

#include "position.hpp"
#include "color.hpp"
#include "renderer.hpp"

namespace libsdlpp {
	class node : public std::enable_shared_from_this<node> {

	public:
        node(position pos = position(0, 0)) :
            parent_(nullptr), visible_(true), handle_events_(true), width_(0), height_(0) {
			set_pos(pos);
        }

		node(std::shared_ptr<node> parent, position pos = position(0,0)) :
			parent_(parent), visible_(true), handle_events_(true), pos_(pos), width_(0), height_(0) {

			if (parent_ == nullptr) {
				parent_ = std::make_shared<node>();
			}

            set_pos(pos);
		}

		virtual ~node() { 
			if (!this->childs_.empty()) {
				this->childs_.clear();
			}
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

		std::shared_ptr<node> parent() {
			return parent_;
		}

		void set_parent(std::shared_ptr<node> parent) {
			parent_ = parent;
			repos();
		}

		bool add_child(const std::string& name, std::shared_ptr<node> child, bool force = true) {

			bool result = true;

			child->set_parent(self());

			if (force) 
			{
				childs_[name] = child;
			}
			else 
			{
				auto ci = childs_.find(name);

				if (ci != childs_.end()) 
				{
					result = false;
				}
				else 
				{
					childs_[name] = child;
				}
			}

			return result;
		}

		void remove_child(const std::string& name) {
			childs_.erase(name);
		}

		void render(sdl_renderer_ptr renderer) {
			if (visible()) {

				on_render(renderer);

				for (auto ci = childs_.begin(); ci != childs_.end(); ci++) {
					if (visible()) {
						ci->second->on_render(renderer);
					}
				}
			}
		}

		void handle_event(const SDL_Event& e) {
			if (handle_events_) {
				on_handle_event(e);

				for (auto ci = childs_.begin(); ci != childs_.end(); ci++) {
					ci->second->on_handle_event(e);
				}
			}
		}

		void async_handle_event(const SDL_Event& e) {
			if (handle_events_) {
				std::future<void> discart = std::async(std::launch::async, std::bind(&node::on_async_handle_event, this, std::placeholders::_1), e);

				for (auto ci = childs_.begin(); ci != childs_.end(); ci++) {
					discart = std::async(std::launch::async, std::bind(&node::on_async_handle_event, ci->second, std::placeholders::_1), e);
				}
			}
		}

	protected:
		std::shared_ptr<node> self() {
			return shared_from_this();
		}

		virtual void repos() {};

	protected:
		virtual void on_handle_event(const SDL_Event& e) {}
		virtual void on_async_handle_event(const SDL_Event& e) {}
		virtual void on_render(sdl_renderer_ptr renderer) {}

	protected:
		std::shared_ptr<node> parent_;

		bool visible_;
		bool handle_events_;

		position pos_;

		uint16_t width_;
		uint16_t height_;

		std::map<std::string, std::shared_ptr<node>> childs_;
	};
}
