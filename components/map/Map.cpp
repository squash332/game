#define CUTE_TILED_IMPLEMENTATION
#include "Map.hpp"

const LoadedTileset *Map::findTileset(int gid)
{
    const LoadedTileset *result = nullptr;
    for (auto &ts : tilesets_)
    {
        if (ts.firstgid <= gid)
        {
            if (!result || ts.firstgid > result->firstgid)
            {
                result = &ts;
            }
        }
    }
    return result;
}

Map::Map(const char *filepath)
{
    map_ = cute_tiled_load_map_from_file(filepath, nullptr);

    if (!map_)
    {
        TraceLog(LOG_ERROR, "Failed to load map: %s", filepath);
        exit(1);
    }

    width_ = map_->width;
    height_ = map_->height;

    cute_tiled_tileset_t *tileset = map_->tilesets;

    while (tileset)
    {
        LoadedTileset lt;
        lt.firstgid = tileset->firstgid;
        lt.columns = tileset->columns;
        lt.texture = LoadTexture("res/mainlevbuild.png");
        tilesets_.push_back(lt);

        tileset = tileset->next;
    }
    cute_tiled_layer_t *layer = map_->layers;

    while (layer)
    {
        cute_tiled_chunk_t *chunk = layer->chunks;
        while (chunk)
        {

            TileLayer layer_temp;
            // checks if current layer is of type tilelayer
            if (strcmp(layer->type.ptr, "tilelayer") == 0)
            {
                layer_temp.height = chunk->height;
                layer_temp.width = chunk->width;
                layer_temp.name = layer->name.ptr;

                for (auto i = 0; i < chunk->data_count; i++)
                {
                    Tile temp_tile;
                    temp_tile.id = chunk->data[i];
                    temp_tile.x = chunk->x + (i % chunk->width);
                    temp_tile.y = chunk->y + (i / chunk->width);

                    if (temp_tile.id != 0)
                    {
                        const LoadedTileset *ts = findTileset(temp_tile.id);
                        int localId = temp_tile.id - ts->firstgid;
                        int col = localId % ts->columns;
                        int row = localId / ts->columns;

                        temp_tile.rectangle = {(float)(col * TILE_SIZE), (float)(row * TILE_SIZE), (float)TILE_SIZE, (float)TILE_SIZE};
                        temp_tile.texture = ts->texture;
                    }

                    layer_temp.tiles.push_back(temp_tile);
                }
                tile_layer_.push_back(layer_temp);
                chunk = chunk->next;
            }
        }

        if (strcmp(layer->type.ptr, "objectgroup") == 0)
        {
            // something
        }

        layer = layer->next;
    }

    std::cout << "MAP: INSTANTIATED" << std::endl;
}

/**
 * Ideally each tile layer has a property which will determine if certain tiles
 * from that layer are walkable or not.
 */
bool Map::isWalkable()
{
}

Map::~Map()
{
    cute_tiled_free_map(map_);
    std::cout << "map freed" << std::endl;
}

uint32_t Map::getCols() const
{
    return width_;
}

uint32_t Map::getRows() const
{
    return height_;
}

const std::vector<TileLayer> &Map::getTileLayers() const
{
    return tile_layer_;
}
