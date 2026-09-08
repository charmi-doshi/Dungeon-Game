#include "FOV.h"

void FOV::compute(Map& map, Point origin, int radius)
{
 
    for (int y = 0; y < MAP_H; ++y)
        for (int x = 0; x < MAP_W; ++x)
            map.at(x, y).visible = false;

   
    map.at(origin.x, origin.y).visible = true;
    map.at(origin.x, origin.y).explored = true;

    
    for (int angle = 0; angle < 360; ++angle)
    {
        float rad = angle * 3.14159265f / 180.0f;
        float endX = origin.x + radius * std::cos(rad);
        float endY = origin.y + radius * std::sin(rad);
        castRay(map, origin, { (int)endX, (int)endY });
    }
}

void FOV::castRay(Map& map, Point from, Point to)
{
    int x0 = from.x, y0 = from.y;
    int x1 = to.x, y1 = to.y;

    int dx = std::abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = std::abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    while (true)
    {
        if (x0 < 0 || x0 >= MAP_W || y0 < 0 || y0 >= MAP_H) return;

        Tile& t = map.at(x0, y0);
        t.visible = true;
        t.explored = true;

        if (t.terrain == Terrain::Wall) return;  
        if (x0 == x1 && y0 == y1) return;        

        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx) { err += dx; y0 += sy; }
    }
}