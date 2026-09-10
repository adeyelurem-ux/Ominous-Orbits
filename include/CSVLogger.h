//
// Created by Michael Adeyelure on 09/09/2026.
//

#ifndef OMINOUS_ORBITS_LOGGER_H
#define OMINOUS_ORBITS_LOGGER_H

#include "Maths/LinearAlgebra/Vector3.h"

#include <fstream>
#include <string>

class CSVLogger {
public:
    explicit CSVLogger(const std::string &filename) {
        file.open(filename);
        if (file.is_open()) {
            file << "sim_years,body_id,pos_x,pos_y,pos_z,vel_x,vel_y,vel_z,acc_x,acc_y,"
                    "acc_z,kinetic\n";
        }
    }

    ~CSVLogger() {
        if (file.is_open()) {
            file.close();
        }
    }

    void log(const double current_time, const int body_id, const double mass, const Vector3 &pos,
             const Vector3 &vel, const Vector3 &acc) {
        if (!file.is_open())
            return;

        const double speed_sq = mod_sqd(vel);
        const double kinetic = 0.5 * mass * speed_sq;

        file << current_time << "," << body_id << "," << pos.x << "," << pos.y << "," << pos.z
             << "," << vel.x << "," << vel.y << "," << vel.z << "," << acc.x << "," << acc.y << ","
             << acc.z << "," << kinetic << "\n";
    }

private:
    std::ofstream file;
};

#endif // OMINOUS_ORBITS_LOGGER_H
