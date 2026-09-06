#include<iostream>

#include "Physics/World.h"

int main() {
    World world;
    world.create_body({0, 0, 0}, 5.9722e24);
    world.create_body({3.844e8, 0, 0}, 7.346e22);

    world.get_body(1).velocity = {0, 1022, 0};

    for (uint64_t i = 0; i < 700000; i ++) {
        world.update(1);
        std::cout << "Iteration " << i << ":\n";
        std::cout << "Earth Position: " << world.get_body(0).position << "\n";
        std::cout << "Earth Velocity: " << world.get_body(0).velocity << "\n";
        std::cout << "Earth Acceleration: " << world.get_body(0).acceleration << "\n\n";
        std::cout << "Moon Position: " << world.get_body(1).position << "\n";
        std::cout << "Moon Velocity: " << world.get_body(1).velocity << "\n";
        std::cout << "Moon Acceleration: " << world.get_body(1).acceleration << "\n\n";
    }

    return 0;
}
