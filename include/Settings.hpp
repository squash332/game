#pragma once

#include "Constants.hpp"

#include "raylib.h"
#include <string>


struct Settings  {
    Rectangle player_frame_config = {10.0f, 10.0f, 80.0f, 20.0f};
    Rectangle targeted_frame_config = {100.0f, 10.0f, 80.0f, 20.0f};
};

void saveSettings(const Settings &settings, const std::string &path);
Settings loadSettings(const std::string &path);