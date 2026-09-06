//
// Created by Michael Adeyelure on 06/09/2026.
//

#include "Physics/World.h"

#include "Physics/Gravity.h"

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


void World::update_grav_fields() {
    for (auto& a : bodies) {
        if (!a.is_alive) continue;

        a.acceleration = {0, 0, 0};
        Vector3 total_g;
        for (auto& b : bodies) {
            if (!b.is_alive) continue;
            if (&a == &b) continue;
            total_g += GravField::evaluate_field_strength(b.position, a.position, b.mass);
        }

        a.acceleration += total_g;
    }
}


void World::update(const double dt) {
    for (auto& body : bodies) {
        body.acceleration = {0, 0, 0};
    }

    update_grav_fields();

    for (auto& body : bodies) {
        if (!body.is_alive) continue;
        body.velocity += body.acceleration * dt;
        body.position += body.velocity * dt;
    }
}
