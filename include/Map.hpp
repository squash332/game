#pragma once

#include "Constants.hpp"
#include <iostream>
#include "cute_tiled.h"
#include <vector>
#include <raylib.h>

struct Tile
{
    int id;
    int x,y;
    Rectangle rectangle;
    Texture2D texture;
};

struct TileLayer
{
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

struct LoadedTileset
{
    int firstgid;
    int columns;
    Texture2D texture;
};
class Map
{
public:
    Map(const char *filepath);
    Map(const Map &other) = delete;
    ~Map();

    bool isWalkable();

    uint32_t getCols() const;
    uint32_t getRows() const;
    const std::vector<TileLayer> &getTileLayers() const;

protected:
private:
    cute_tiled_map_t *map_;
    int width_;
    int height_;

    const LoadedTileset *findTileset(int gid);

    std::vector<TileLayer> tile_layer_;
    std::vector<Object> object_;
    std::vector<LoadedTileset> tilesets_;
};
