//
// Created by Michael Adeyelure on 10/09/2026.
//

#ifndef OMINOUS_ORBITS_JSON_INIT_H
#define OMINOUS_ORBITS_JSON_INIT_H

#include "Physics/World.h"

#include <array>
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
    static std::array<bool, 2> get_logging_info(const std::string &filepath);
};

#endif // OMINOUS_ORBITS_JSON_INIT_H
