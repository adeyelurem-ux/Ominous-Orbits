//
// Created by Michael Adeyelure on 06/09/2026.
//

#ifndef OMINOUS_ORBITS_RK2_H
#define OMINOUS_ORBITS_RK2_H
#include "../LinearAlgebra/Vector3.h"

#include <functional>

class RK2 {
    using GradientFunc = std::function<Vector3(const Vector3 &, double t)>;

public:
    [[nodiscard]] static Vector3 delta(const Vector3 &state, const double t, const double dt,
                                       const GradientFunc &grad) {
        const Vector3 mid_grad = grad(state + grad(state, t) * (dt / 2), t + dt / 2);
        return mid_grad * dt;
    }
};

#endif // OMINOUS_ORBITS_RK2_H
