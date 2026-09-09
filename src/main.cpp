#include "Logger.h"
#include "Renderer2D.h"
#include "Maths/Units.h"
#include "Physics/World.h"

#include <chrono>
#include <sstream>

int main() {
    const Renderer2D renderer("Ominous Orbits - N-Body Simulator", 1280, 720);
    if (!renderer.is_initialised()) return -1;

    World world;
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;

    ss << std::put_time(std::localtime(&in_time_t), "Y%m%d_%H%M%S") << "orbital_data.csv";

    Logger logger(ss.str());

    world.create_body({0, 0, 0}, 1.0);
    world.create_body({1, 0, 0}, 3.003489616e-6);
    world.get_body(1).velocity = {0, 2.0 * std::numbers::pi, 0};
    world.update_grav_fields();

    bool running = true;
    SDL_Event event;

    constexpr double physics_dt_years = 1.0 / (365.0 * 100);
    constexpr double sim_years_per_real_second = 0.1;

    double sim_time_elapsed = 0.0;
    double sim_time_accumulator = 0.0;
    auto previous_time = std::chrono::high_resolution_clock::now();

    while (running) {
        auto current_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> real_frame_time = current_time - previous_time;
        previous_time = current_time;

        const double real_dt = std::min(real_frame_time.count(), 0.25);

        const double sim_dt_passed = real_dt * sim_years_per_real_second;
        sim_time_accumulator += sim_dt_passed;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
        }

        while (sim_time_accumulator >= physics_dt_years) {
            world.update(physics_dt_years);
            sim_time_accumulator -= physics_dt_years;
        }

        sim_time_elapsed += sim_dt_passed;

        for (std::size_t i = 0; i < world.get_bodies().size(); i++) {
            Body& body = world.get_body(i);

            logger.log(sim_time_elapsed, static_cast<int>(i), body.mass, body.position, body.velocity, body.acceleration);
        }

        renderer.clear();
        renderer.render_world(world);
        renderer.present();
    }

    return 0;
}