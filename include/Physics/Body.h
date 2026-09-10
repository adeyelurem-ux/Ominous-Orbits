//
// Created by Michael Adeyelure on 06/09/2026.
//

#ifndef OMINOUS_ORBITS_BODY_H
#define OMINOUS_ORBITS_BODY_H

#include "Maths/LinearAlgebra/Vector3.h"

struct Body {
    Vector3 position = {0, 0, 0};
    Vector3 velocity = {0, 0, 0};
    Vector3 acceleration = {0, 0, 0};
    Vector3 net_force = {0, 0, 0};

    double mass = 1;

    bool is_alive = true;
};

#endif // OMINOUS_ORBITS_BODY_H
