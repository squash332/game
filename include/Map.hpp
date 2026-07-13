#pragma once

#include "Constants.hpp"
#include <iostream>
#include "cute_tiled.h"

class Map
{
public:
    Map(const char* filepath);
    Map(const Map &other) = default;
    ~Map();

    uint32_t getWidth();
    uint32_t getHeight();
    void setWidth(int w);
    void setHeight(int h);

protected:
private:
    cute_tiled_map_t* map_;
    int width_;
    int height_;

};


