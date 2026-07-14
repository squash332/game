#define CUTE_TILED_IMPLEMENTATION
#include "Map.hpp"

Map::Map(const char *filepath)
{
    map_ = cute_tiled_load_map_from_file(filepath, nullptr);

    if (!map_)
    {
        TraceLog(LOG_ERROR, "Failed to load map: %s", filepath);
        exit(1);
    }
    // get map width and height
    int w = map_->width;
    int h = map_->height;
    cute_tiled_layer_t *layer = map_->layers;
    while (layer) {
    
        for (auto i = 0; i < layer->data_count; i++) {
            int gid = layer->data[i];
            auto x = i % w;
            auto y = i / w;
            // TraceLog(LOG_INFO, "GID[%d][%d] = %d", x, y, gid);
    
        }
        layer = layer->next;
    }


    std::cout << "MAP: INSTANTIATED" << std::endl;
}

Map::~Map()
{
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
