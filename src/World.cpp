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
    const double half_dt = dt * 0.5;

    // 1. First velocity half-step & full position step
    for (auto& body : bodies) {
        if (!body.is_alive) continue;

        body.velocity += body.acceleration * half_dt;
        body.position += body.velocity * dt;
    }

    // 2. Compute new accelerations at updated positions
    update_grav_fields();

    // 3. Second velocity half-step using NEW accelerations
    for (auto& body : bodies) {
        if (!body.is_alive) continue;

        body.velocity += body.acceleration * half_dt;
    }
}
