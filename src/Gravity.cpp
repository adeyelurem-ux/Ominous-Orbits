//
// Created by Michael Adeyelure on 06/09/2026.
#include <cmath>

#include "Physics/Gravity.h"
#include "Maths/Units.h"


/**
 *
 * @param source_pos Position of source particle
 * @param target_pos Position of target particle
 * @param source_mass Mass of source particle
 * @return Acceleration due to gravity in the target position
 */
[[nodiscard]] Vector3 GravField::evaluate_field_strength(const Vector3& source_pos,
    const Vector3& target_pos, const double source_mass) {
    
    const Vector3 rad_vector = source_pos - target_pos;
    const double r_sqd = mod_sqd(rad_vector);

    if (r_sqd == 0) {
        return Vector3{0, 0, 0};
    }

    const double r_cubed = r_sqd * std::sqrt(r_sqd);

    return rad_vector * (G * source_mass / r_cubed);
}
