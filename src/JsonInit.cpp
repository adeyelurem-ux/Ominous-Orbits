//
// Created by Michael Adeyelure on 10/09/2026.
//

#include "JsonInit.h"

bool JsonInit::load_world_from_json(const std::string &filepath, World &world) {
    if (!fs::exists(filepath)) {
        std::cerr << "JSON Loader Error. File not found at filepath: " << filepath << "\n";
        return false;
    }

    FILE *fp = fopen(filepath.c_str(), "r");
    if (!fp) {
        std::cerr << "Unable to open file: " << filepath << "\n";
        return false;
    }

    char read_buffer[65536];

    rapidjson::FileReadStream stream(fp, read_buffer, sizeof(read_buffer));

    rapidjson::Document doc;
    doc.ParseStream(stream);
    fclose(fp);

    if (doc.HasParseError()) {
        std::cerr << "JSON Parse Error: " << doc.GetParseError() << " (at offset "
                  << doc.GetErrorOffset() << ")\n";
        return false;
    }

    if (!doc.IsObject() || !doc.HasMember("bodies") || !doc["bodies"].IsArray()) {
        std::cerr << "JSON Schema Error: Missing array field 'bodies' at root level.\n";
        return false;
    }

    const rapidjson::Value &bodies_array = doc["bodies"];

    for (rapidjson::SizeType i = 0; i < bodies_array.Size(); ++i) {
        const auto &b = bodies_array[i];

        if (!b.IsObject())
            continue;

        // Extract required numeric fields safely
        double mass = b.HasMember("mass") && b["mass"].IsNumber() ? b["mass"].GetDouble() : 1.0;
        double density =
            b.HasMember("density") && b["density"].IsNumber() ? b["density"].GetDouble() : 3000.0;

        // Extract position vector [x, y, z]
        Vector3 pos{0.0, 0.0, 0.0};
        if (b.HasMember("position") && b["position"].IsArray() && b["position"].Size() == 3) {
            pos.x = b["position"][0].GetDouble();
            pos.y = b["position"][1].GetDouble();
            pos.z = b["position"][2].GetDouble();
        }

        // Extract velocity vector [vx, vy, vz]
        Vector3 vel{0.0, 0.0, 0.0};
        if (b.HasMember("velocity") && b["velocity"].IsArray() && b["velocity"].Size() == 3) {
            vel.x = b["velocity"][0].GetDouble();
            vel.y = b["velocity"][1].GetDouble();
            vel.z = b["velocity"][2].GetDouble();
        }

        // Instantiate body in the physics world
        std::size_t body_idx = world.create_body(pos, mass);
        Body &body = world.get_body(body_idx);
        body.velocity = vel;
        body.density = density;
        body.update_radius_au();
    }

    // Compute initial gravitational fields across loaded bodies
    world.update_grav_fields();
    return true;
}

std::array<bool, 2> JsonInit::get_logging_info(const std::string &filepath) {
    std::array log_settings {false, false}; // index 0 asks if logging, index 1 asks if logging on render
    if (!fs::exists(filepath)) {
        std::cerr << "JSON Loader Error. File not found at filepath: " << filepath << "\n";
        return log_settings;
    }

    FILE *fp = fopen(filepath.c_str(), "r");
    if (!fp) {
        std::cerr << "Unable to open file: " << filepath << "\n";
        return log_settings;
    }

    char read_buffer[65536];

    rapidjson::FileReadStream stream(fp, read_buffer, sizeof(read_buffer));

    rapidjson::Document doc;
    doc.ParseStream(stream);
    fclose(fp);

    log_settings[0] = doc["logging"].GetBool();
    log_settings[1] = doc["log_at_render"].GetBool();

    return log_settings;
}
