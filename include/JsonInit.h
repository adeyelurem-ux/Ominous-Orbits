//
// Created by Michael Adeyelure on 10/09/2026.
//

#ifndef OMINOUS_ORBITS_JSON_INIT_H
#define OMINOUS_ORBITS_JSON_INIT_H

#include "Physics/World.h"

#include <cstdio>
#include <filesystem>
#include <iostream>
#include <string>

#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

namespace fs = std::filesystem;

class JsonInit {
public:
    static bool load_world_from_json(const std::string &filepath, World &world);
};

#endif // OMINOUS_ORBITS_JSON_INIT_H
