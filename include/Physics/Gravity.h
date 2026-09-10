//
// Created by Michael Adeyelure on 06/09/2026.
//

#ifndef OMINOUS_ORBITS_GRAVITY_H
#define OMINOUS_ORBITS_GRAVITY_H

#include "Body.h"

class GravField {
public:
    [[nodiscard]] static Vector3 evaluate_field_strength(const Vector3 &source_pos,
                                                         const Vector3 &target_pos,
                                                         double source_mass);
};

#endif // OMINOUS_ORBITS_GRAVITY_H
