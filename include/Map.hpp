#pragma once

#include "Constants.hpp"
#include <iostream>
#include "cute_tiled.h"
#include <vector>
#include <raylib.h>

struct Tile
{
    uint32_t id;
    Rectangle rectangle;
    Texture2D texture;
};

struct TileLayer {
    std::string name;
    uint32_t width;
    uint32_t height;
    std::vector<Tile> tiles;
};

struct Object
{
    std::string type;
    Rectangle rectangle;
    bool lootable = true;
};
class Map
{
public:
    Map(const char *filepath);
    Map(const Map &other) = delete;
    ~Map();

    uint32_t getWidth();
    uint32_t getHeight();
    void setWidth(int w);
    void setHeight(int h);

protected:
private:
    cute_tiled_map_t *map_;
    int width_;
    int height_;

    std::vector<TileLayer> tile_layer_;
    std::vector<Object> object_;
};
