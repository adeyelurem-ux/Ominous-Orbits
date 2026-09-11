#include "CSVLogger.h"
#include "JsonInit.h"
#include "Maths/Units.h"
#include "Physics/World.h"
#include "Renderer2D.h"

#include <chrono>
#include <optional>
#include <sstream>

namespace fs = std::filesystem;

int main() {
    // Logging setup
    bool logging = JsonInit::get_logging_info("config/init.json")[0];
    bool log_at_render = JsonInit::get_logging_info("config/init.json")[1];

    std::optional<CSVLogger> csv_logger;

    if (logging) {
        fs::create_directories("orbit_outputs");

        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;

        ss << std::put_time(std::localtime(&in_time_t), "%Y%m%d_%H%M%S") << "orbital_data.csv";

        csv_logger.emplace("orbit_outputs/" + ss.str());
    }

    Renderer2D renderer("Ominous Orbits - N-Body Simulator", 1280, 720);
    if (!renderer.is_initialised())
        return -1;

    World world;

    Text text_engine;

    if (!text_engine.init()) {
        std::cerr << "TTF initialisation failed: " << SDL_GetError() << "\n";
    }

    if (!text_engine.loadFont("assets/american-typewriter.ttf", 18.0)) {
        std::cerr << "Font loading failed: " << SDL_GetError() << "\n";
    }

    // Initialisation
    JsonInit::load_world_from_json("config/init.json", world);

    // Update Loop
    bool running = true;
    SDL_Event event;

    constexpr double physics_dt_years = 1.0 / (365.0 * 100);
    constexpr double sim_years_per_real_second = 0.1;

    double sim_time_elapsed = 0.0;
    double sim_time_accumulator = 0.0;
    auto previous_time = std::chrono::high_resolution_clock::now();

    constexpr double TARGET_FPS = 60.0;
    constexpr double RENDER_INTERVAL = 1.0 / TARGET_FPS; // ~0.01667 seconds

    double render_accumulator = 0.0;

    while (running) {
        auto current_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> real_frame_time = current_time - previous_time;
        previous_time = current_time;

        const double real_dt = std::min(real_frame_time.count(), 0.25); // Clamp spikes

        // 1. Advance simulation accumulator
        const double sim_dt_passed = real_dt * sim_years_per_real_second;
        sim_time_accumulator += sim_dt_passed;
        sim_time_elapsed += sim_dt_passed;

        // 2. Track real time passed for rendering
        render_accumulator += real_dt;

        if (logging) {
            std::size_t i = 0;
            for (auto &body : world.get_bodies()) {
                csv_logger->log(sim_time_elapsed, i, body.mass, body.position, body.velocity,
                                body.acceleration);
                i++;
            }
        }

        // Handle window events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT)
                running = false;

            else if (event.type == SDL_EVENT_MOUSE_WHEEL) {
                float mouse_x = event.wheel.mouse_x;
                float mouse_y = event.wheel.mouse_y;

                if (event.wheel.y > 0) {
                    renderer.zoom_at(1.1, mouse_x, mouse_y);
                }

                else if (event.wheel.y < 0) {
                    renderer.zoom_at(0.9, mouse_x, mouse_y);
                }
            }

            else if (event.type == SDL_EVENT_KEY_DOWN) {
                switch (event.key.key) {
                case SDLK_ESCAPE:
                    running = false;
                    break;

                case SDLK_K:
                    renderer.reset_pan();
                    renderer.reset_scale();

                default:
                    break;
                }
            }

            else if (event.type == SDL_EVENT_MOUSE_MOTION) {
                if (event.motion.state & SDL_BUTTON_LMASK) {
                    renderer.pan(event.motion.xrel, event.motion.yrel);
                }
            }
        }

        // 3. Step physics as many times as needed for stability
        while (sim_time_accumulator >= physics_dt_years) {
            world.update(physics_dt_years);
            sim_time_accumulator -= physics_dt_years;
        }

        // 4. Render ONLY when 1/60th of a second of real time has passed
        if (render_accumulator >= RENDER_INTERVAL) {
            renderer.clear();
            renderer.render_world(world);
            renderer.drawText(text_engine, 10.0, 10.0,
                              "Sim years: " + std::to_string(sim_time_elapsed),
                              {255, 255, 255, 255});
            renderer.present();

            // Subtract interval to keep surplus time for the next frame
            render_accumulator -= RENDER_INTERVAL;

            if (logging && log_at_render) {
                std::size_t i = 0;
                for (auto &body : world.get_bodies()) {
                    csv_logger->log(sim_time_elapsed, i, body.mass, body.position, body.velocity,
                                    body.acceleration);

                    i++;
                }
            }
        }
    }

    return 0;
}