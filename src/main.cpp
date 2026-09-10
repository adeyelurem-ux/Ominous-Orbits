#include "CSVLogger.h"
#include "Maths/Units.h"
#include "Physics/World.h"
#include "Renderer2D.h"

#include <chrono>
#include <sstream>
#include <optional>

namespace fs = std::filesystem;

int main() {
    // Logging setup
    bool logging = false;
    bool log_on_render = true;

    std::optional<CSVLogger> csv_logger;

    if (logging) {
        fs::create_directories("orbit_outputs");

        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;

        ss << std::put_time(std::localtime(&in_time_t), "%Y%m%d_%H%M%S") << "orbital_data.csv";

        csv_logger.emplace("orbit_outputs/" + ss.str());
    }

    const Renderer2D renderer("Ominous Orbits - N-Body Simulator", 1280, 720);
    if (!renderer.is_initialised())
        return -1;

    World world;

    // Initialisation
    world.create_body({0, 0, 0}, 1.0);
    world.create_body({1, 0, 0}, 3.003489616e-6);
    world.get_body(0).density = 1408; world.get_body(0).update_radius_au();
    world.get_body(1).velocity = {0, 2.0 * std::numbers::pi, 0};
    world.get_body(1).density = 5514; world.get_body(1).update_radius_au();
    world.update_grav_fields();

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

        // Handle window events
        while (SDL_PollEvent(&event)) { 
            if (event.type == SDL_EVENT_QUIT) 
                running = false; 
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
            renderer.present(); 

            // Subtract interval to keep surplus time for the next frame
            render_accumulator -= RENDER_INTERVAL;

            if (logging && log_on_render) {
                const std::size_t i = 0;
                for (auto& body : world.get_bodies()) {
                    csv_logger->log(sim_time_elapsed, i, body.mass, body.position, body.velocity, body.acceleration);
                }
            }
        }
    }

    return 0;
}