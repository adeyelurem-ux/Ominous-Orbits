//
// Created by Michael Adeyelure on 08/09/2026.
//

#include "Renderer2D.h"

#include <cmath>
#include <iostream>
#include <vector>

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

void Renderer2D::drawFilledCircle(const float centre_x, const float centre_y, float radius,
                                  int segments, const SDL_FColor &colour) const {
    std::vector<SDL_Vertex> vertices;
    std::vector<int> indices;

    vertices.push_back({.position = {.x = centre_x, .y = centre_y},
                        .color = colour,
                        .tex_coord = {.x = 0.0f, .y = 0.0f}});

    for (int i = 0; i <= segments; ++i) {
        float angle = static_cast<float>(i) * (2.0f * 3.14159265f / static_cast<float>(segments));
        float x = centre_x + radius * std::cos(angle);
        float y = centre_y + radius * std::sin(angle);

        vertices.push_back({.position = {.x = x, .y = y},
                            .color = colour,
                            .tex_coord = {.x = 0, .y = 0}});

        if (i > 0) {
            indices.push_back(0);     // Center
            indices.push_back(i);     // Current point
            indices.push_back(i + 1); // Next point
        }
    }

    SDL_RenderGeometry(sdl_renderer, nullptr, vertices.data(), static_cast<int>(vertices.size()),
                       indices.data(), static_cast<int>(indices.size()));
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
        const auto screen_radius = std::max(3.0f ,static_cast<float>(body.radius * scale));

        SDL_FColor colour = (body.mass > 0.5) ? SDL_FColor{1.0f, 0.92f, 0.0f, 1.0f}
                                              : SDL_FColor{0.2f, 0.6f, 1.0f, 1.0f};

        drawFilledCircle(screen_pos.x, screen_pos.y, screen_radius, 32, colour);
    }
}

void Renderer2D::present() const {
    SDL_RenderPresent(sdl_renderer);
}
