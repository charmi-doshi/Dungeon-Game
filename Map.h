#pragma once
#include "Common.h"
#include "Tile.h"
#include <vector>

class Map
{
public:
    Map();

    void clear(Terrain terrain = Terrain::Wall);
    bool inBounds(int x, int y) const;
    bool inBounds(Point p) const;

    Tile& at(int x, int y);
    const Tile& at(int x, int y) const;

    Tile& at(Point p);
    const Tile& at(Point p) const;

    Point startingPosition() const { return startingPosition_; }
    void setStartingPosition(Point p) { startingPosition_ = p; }

private:
    std::vector<Tile> tiles_;
    Point startingPosition_ = { 0, 0 };
}; 
