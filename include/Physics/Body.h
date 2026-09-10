//
// Created by Michael Adeyelure on 06/09/2026.
//

#ifndef OMINOUS_ORBITS_BODY_H
#define OMINOUS_ORBITS_BODY_H

#include "Maths/LinearAlgebra/Vector3.h"
#include "Maths/Units.h"

#include <cmath>
#include <numbers>

struct Body {
    Vector3 position = {0, 0, 0};
    Vector3 velocity = {0, 0, 0};
    Vector3 acceleration = {0, 0, 0};
    Vector3 net_force = {0, 0, 0};

    double mass = 1;    // solar masses
    double density = 1; // kilograms per metre-cubed
    double radius =
        std::cbrt(3.0 * mass / (4.0 * std::numbers::pi * SI_TO_ASTRONOMICAL_DENSITY * density)); // AU

    void update_radius_au() {
        radius = std::cbrt(3.0 * mass / (4.0 * std::numbers::pi * SI_TO_ASTRONOMICAL_DENSITY * density));
    }

    bool is_alive = true;
};

#endif // OMINOUS_ORBITS_BODY_H
