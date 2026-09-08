#include "Maths/Units.h"
#include "Physics/World.h"

#include<iostream>

int main() {
    World world;
    world.create_body({0, 0, 0}, 1);
    world.create_body({1, 0, 0}, 3.003489616e-6);

    world.get_body(1).velocity = {0, 2.0 * std::numbers::pi, 0};
    world.update_grav_fields();

    for (uint64_t i = 0; i < 730; i ++) {
        world.update(1.0/365);
        if (i % 365 != 0) continue;
        std::cout << "Iteration " << i << ":\n";
        std::cout << "Sun Position: " << world.get_body(0).position << "\n";
        std::cout << "Sun Velocity: " << world.get_body(0).velocity << "\n";
        std::cout << "Sun Acceleration: " << world.get_body(0).acceleration << "\n\n";
        std::cout << "Earth Position: " << world.get_body(1).position << "\n";
        std::cout << "Earth Velocity: " << world.get_body(1).velocity << "\n";
        std::cout << "Earth Acceleration: " << world.get_body(1).acceleration << "\n\n";
    }

    return 0;
}
