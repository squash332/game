#include "Settings.hpp"

#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void to_json(json &j, const Rectangle &r)
{
    j = json{{"x", r.x}, {"y", r.y}, {"width", r.width}, {"height", r.height}};
}

void from_json(const json &j, Rectangle &r)
{
    j.at("x").get_to(r.x);
    j.at("y").get_to(r.y);
    j.at("width").get_to(r.width);
    j.at("height").get_to(r.height);
}

void saveSettings(const Settings &settings, const std::string &path)
{
    json j;
    j["player_frame_config"] = settings.player_frame_config;
    j["target_frame_config"] = settings.targeted_frame_config;

    std::ofstream file(path);
    file << j.dump(4);
}

Settings loadSettings(const std::string &path)
{
    Settings settings;

    std::ifstream file(path);
    if (!file)
        return settings;

    json j = json::parse(file);
    settings.player_frame_config = j["player_frame_config"].get<Rectangle>();
    settings.targeted_frame_config = j["targeted_frame_config"].get<Rectangle>();

    return settings;
}
