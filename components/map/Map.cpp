#define CUTE_TILED_IMPLEMENTATION
#include "Map.hpp"

Map::Map(const char* filepath)
{
    map_ = cute_tiled_load_map_from_file(filepath, nullptr);
    std::cout  << "MAP: INSTANTIATED" << std::endl;
}

Map::~Map() {
    cute_tiled_free_map(map_);
    std::cout << "map freed" << std::endl;
}

uint32_t Map::getWidth()
{
    return width_;
}

uint32_t Map::getHeight()
{
    return height_;
}

void Map::setWidth(int w)
{
    width_ = w;
}

void Map::setHeight(int h)
{
    height_ = h;
}
