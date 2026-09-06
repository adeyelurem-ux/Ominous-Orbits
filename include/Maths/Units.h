//
// Created by Michael Adeyelure on 06/09/2026.
//

#ifndef OMINOUS_ORBITS_UNITS_H
#define OMINOUS_ORBITS_UNITS_H

#include <numbers>

constexpr double AU_TO_M = 1.495978707e11;
constexpr double DAYS_TO_SECS = 86400;
constexpr double SOLAR_TO_KG = 1.988416e30;
constexpr double G = 4 * std::numbers::pi * std::numbers::pi; //distance in AU, mass in solar masses, time in years

#endif //OMINOUS_ORBITS_UNITS_H
