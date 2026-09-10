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

    void zoom(const double new_zoom) { scale = std::clamp(scale * new_zoom, 10.0, 5000.0); }
    void zoom_at(const double factor, const float mouse_x, const float mouse_y) {
        // Clamp zoom scale within reasonable bounds
        double new_scale = std::clamp(scale * factor, 1.0, 50000.0);
        double actual_factor = new_scale / scale;

        // Calculate mouse position relative to the screen center
        double center_x = window_width * 0.5;
        double center_y = window_height * 0.5;

        // Shift offsets so the point under the cursor stays fixed
        x_offset -= (mouse_x - center_x - x_offset) * (actual_factor - 1.0);
        y_offset -= (mouse_y - center_y - y_offset) * (actual_factor - 1.0);

        scale = new_scale;
    }
    void pan(const double dx, const double dy) {
        x_offset += dx;
        y_offset += dy;
    }

    void reset_scale() { scale = 600; }
    void reset_pan() { x_offset = 0.0; y_offset = 0.0; }

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
