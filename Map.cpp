#include "Map.h"

Map::Map()
{
    tiles_.resize(MAP_W * MAP_H);
    clear(Terrain::Wall);
}

void Map::clear(Terrain terrain)
{
    for (auto& tile : tiles_)
    {
        tile.terrain = terrain;
        tile.explored = false;
        tile.visible = false;
    }
}

bool Map::inBounds(int x, int y) const
{
    return x >= 0 && x < MAP_W && y >= 0 && y < MAP_H;
}

bool Map::inBounds(Point p) const
{
    return inBounds(p.x, p.y);
}

Tile& Map::at(int x, int y)
{
    return tiles_[y * MAP_W + x];
}

const Tile& Map::at(int x, int y) const
{
    return tiles_[y * MAP_W + x];
}

Tile& Map::at(Point p)
{
    return at(p.x, p.y);
}

const Tile& Map::at(Point p) const
{
    return at(p.x, p.y);
}