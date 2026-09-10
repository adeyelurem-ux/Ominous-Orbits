//
// Created by Michael Adeyelure on 08/09/2026.
//

#ifndef OMINOUS_ORBITS_RENDERER_H
#define OMINOUS_ORBITS_RENDERER_H

#include <SDL3/SDL.h>

#include "Physics/World.h"

class Renderer2D {
public:
    Renderer2D(const char *title, int width, int height);
    ~Renderer2D();

    Renderer2D(const Renderer2D &) = delete;
    Renderer2D &operator=(const Renderer2D &) = delete;

    [[nodiscard]] bool is_initialised() const { return initialised; }

    void drawFilledCircle(float centre_x, float centre_y, float radius, int segments,
                          const SDL_FColor &colour) const;

    void clear() const;
    void render_world(World &world) const;
    void present() const;

    void zoom(const double new_zoom) { scale = std::clamp(scale * new_zoom, 10.0, 5000.0);}
    void pan(const double dx, const double dy) {
        x_offset += dx;
        y_offset += dy;
    }

private:
    SDL_Window *window = nullptr;
    SDL_Renderer *sdl_renderer = nullptr;

    bool initialised = false;
    int window_width;
    int window_height;

    double scale = 600.0; // pixels per AU
    double x_offset = 0.0;
    double y_offset = 0.0;

    [[nodiscard]] SDL_FPoint au_to_screen(const Vector3 &pos) const;
};

#endif // OMINOUS_ORBITS_RENDERER_H
