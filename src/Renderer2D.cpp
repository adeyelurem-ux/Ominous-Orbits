//
// Created by Michael Adeyelure on 08/09/2026.
//

#include "Renderer2D.h"

#include <iostream>

Renderer2D::Renderer2D(const char *title, const int width, const int height)
    : window_width(width), window_height(height) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL initialisation failed: " << SDL_GetError() << "\n";
        return;
    }

    window = SDL_CreateWindow(title, width, height, 0);
    if (!window) {
        std::cerr << "SDL Window initialisation failed: " << SDL_GetError() << "\n";
        return;
    }

    sdl_renderer = SDL_CreateRenderer(window, nullptr);
    initialised = true;
}

Renderer2D::~Renderer2D() {
    if (sdl_renderer)
        SDL_DestroyRenderer(sdl_renderer);
    if (window)
        SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_FPoint Renderer2D::au_to_screen(const Vector3 &pos) const {
    const double x_centre = window_width * 0.5 + x_offset;
    const double y_centre = window_height * 0.5 + y_offset;

    return SDL_FPoint{.x = static_cast<float>(x_centre + (pos.x * scale)),
                      .y = static_cast<float>(y_centre - (pos.y * scale))};
}

void Renderer2D::clear() const {
    SDL_SetRenderDrawColor(sdl_renderer, 10, 10, 15, 255);
    SDL_RenderClear(sdl_renderer);
}

void Renderer2D::render_world(World &world) const {
    for (auto &body : world.get_bodies()) {
        if (!body.is_alive)
            continue;

        SDL_FPoint screen_pos = au_to_screen(body.position);
        const float size = (body.mass > 0.5) ? 12.0 : 8.0;

        SDL_FRect rect = {
            .x = screen_pos.x - size * 0.5f, .y = screen_pos.y - size * 0.5f, .w = size, .h = size};

        // Sun = Yellow, Earth/Other = Light Blue
        if (body.mass >= 0.5) {
            SDL_SetRenderDrawColor(sdl_renderer, 255, 220, 50, 255);
        } else {
            SDL_SetRenderDrawColor(sdl_renderer, 100, 200, 255, 255);
        }

        SDL_RenderFillRect(sdl_renderer, &rect);
    }
}

void Renderer2D::present() const {
    SDL_RenderPresent(sdl_renderer);
}
