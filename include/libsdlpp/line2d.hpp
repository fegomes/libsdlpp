#pragma once

#include "color.hpp"

namespace libsdlpp {
    class line2d : public node {
    public:
        line2d(position p1 = position(0, 0), position p2 = position(0, 0), color c = color::black()) :
            node(nullptr), p1_(p1), p2_(p2), color_(c) {
        }

        line2d(std::shared_ptr<node> parent, position p1 = position(0, 0), position p2 = position(0, 0), color c = color::black()) :
            node(parent), p1_(p1), p2_(p2), color_(c) {
        }

        void set_color(color c) {
            this->color_ = c;
        }

        void on_render(sdl_renderer_ptr renderer) {

            SDL_SetRenderDrawColor(
                renderer.get(),
                color_.red_,
                color_.green_,
                color_.blue_,
                color_.alpha_);

            SDL_RenderDrawLine(renderer.get(),
                p1_.x() + parent()->pos().x(),
                p1_.y() + parent()->pos().y(),
                p2_.x() + parent()->pos().x(),
                p2_.y() + parent()->pos().y());
        }

    private:
        color color_;

        position p1_;
        position p2_;

    };
}