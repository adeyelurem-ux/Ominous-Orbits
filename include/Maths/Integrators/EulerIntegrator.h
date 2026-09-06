//
// Created by Michael Adeyelure on 06/09/2026.
//

#ifndef OMINOUS_ORBITS_EULERINTEGRATOR_H
#define OMINOUS_ORBITS_EULERINTEGRATOR_H
#include "Maths/LinearAlgebra/Vector3.h"

#include <functional>


class EulerIntegrator {
    using GradientFunc = std::function<Vector3(const Vector3&, double)>;
public:
    [[nodiscard]] static Vector3 delta(const Vector3& state, const double t, const double dt, const GradientFunc& grad) {
        return grad(state, t) * dt;
    }
};

#endif //OMINOUS_ORBITS_EULERINTEGRATOR_H
