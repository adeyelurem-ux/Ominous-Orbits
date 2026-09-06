//
// Created by Michael Adeyelure on 06/09/2026.
//

#include "Physics/World.h"

std::size_t World::create_body(const Vector3 &position, const double mass) {
    Body body;
    body.position = position;
    body.mass = mass;

    if (!free_indices.empty()) {
        const std::size_t target = free_indices.back();
        free_indices.pop_back();

        bodies[target] = body;

        return target;
    }

    bodies.push_back(body);

    return bodies.size() - 1;
}


void World::destroy_body(const std::size_t index) {
    if (!bodies[index].is_alive) return;

    bodies[index].is_alive = false;
    free_indices.push_back(index);
}
