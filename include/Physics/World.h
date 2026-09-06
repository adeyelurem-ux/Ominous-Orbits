//
// Created by Michael Adeyelure on 06/09/2026.
//

#ifndef OMINOUS_ORBITS_WORLD_H
#define OMINOUS_ORBITS_WORLD_H

#include <cstddef>
#include <vector>

#include "Body.h"

class World {
public:
    std::size_t create_body(const Vector3 &position, double mass);
    void destroy_body(std::size_t index);

    Body& get_body(const std::size_t index){return bodies[index];}
    std::vector<Body>& get_bodies(){return bodies;}

    void update_grav_fields();
    void update();

private:
    std::vector<Body> bodies;
    std::vector<std::size_t> free_indices;
};

#endif //OMINOUS_ORBITS_WORLD_H
