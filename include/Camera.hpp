#pragma once

#include "raylib.h"
#include "math.h"
#include "Constants.hpp"

class Cam2d
{
public:
    Cam2d();
    Cam2d(const Cam2d &other) = delete;
    ~Cam2d() = default;

    void beginFrame();
    void update(float, float, float);
    void endFrame();
    void handleZoom();
    void resetZoom();

protected:
private:
    Camera2D camera_;
};