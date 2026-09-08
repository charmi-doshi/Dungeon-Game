// MapGen.cpp
#include "MapGen.h"
#include <cstdlib>
#include <algorithm>

void MapGen::generate(Map& map, int maxDepth)
{
    map.clear(Terrain::Wall);

    std::vector<BSPNode> nodes;
    BSPNode root;
    root.region = { 1, 1, MAP_W - 2, MAP_H - 2 };
    nodes.push_back(root);

    split(0, nodes, maxDepth, map);
}

void MapGen::split(int idx, std::vector<BSPNode>& nodes, int depth, Map& map)
{
    if (depth == 0 || nodes[idx].region.w < 12 || nodes[idx].region.h < 12)
    {
        placeRoom(idx, nodes, map);
        return;
    }

    bool horizontal = (nodes[idx].region.w < nodes[idx].region.h) ||
        (nodes[idx].region.w == nodes[idx].region.h && rand() % 2 == 0);

    int splitPos = 0;
    if (horizontal)
    {
        splitPos = nodes[idx].region.y + nodes[idx].region.h / 3 + rand() % (nodes[idx].region.h / 3);
    }
    else
    {
        splitPos = nodes[idx].region.x + nodes[idx].region.w / 3 + rand() % (nodes[idx].region.w / 3);
    }

    BSPNode leftNode, rightNode;
    if (horizontal)
    {
        leftNode.region = { nodes[idx].region.x, nodes[idx].region.y,
                             nodes[idx].region.w, splitPos - nodes[idx].region.y };
        rightNode.region = { nodes[idx].region.x, splitPos,
                             nodes[idx].region.w, nodes[idx].region.y + nodes[idx].region.h - splitPos };
    }
    else
    {
        leftNode.region = { nodes[idx].region.x, nodes[idx].region.y,
                             splitPos - nodes[idx].region.x, nodes[idx].region.h };
        rightNode.region = { splitPos, nodes[idx].region.y,
                             nodes[idx].region.x + nodes[idx].region.w - splitPos, nodes[idx].region.h };
    }

    
    nodes[idx].left = (int)nodes.size();
    nodes.push_back(leftNode);
    nodes[idx].right = (int)nodes.size();
    nodes.push_back(rightNode);

   
    int leftIdx = nodes[idx].left;
    int rightIdx = nodes[idx].right;

    split(leftIdx, nodes, depth - 1, map);
    split(rightIdx, nodes, depth - 1, map);

    connectChildren(idx, nodes, map);
}

void MapGen::placeRoom(int idx, std::vector<BSPNode>& nodes, Map& map)
{
    const SDL_Rect& reg = nodes[idx].region;

    int roomW = std::max(4, reg.w - 2 - (rand() % 3));
    int roomH = std::max(4, reg.h - 2 - (rand() % 3));
    int roomX = reg.x + 1 + rand() % std::max(1, reg.w - roomW - 1);
    int roomY = reg.y + 1 + rand() % std::max(1, reg.h - roomH - 1);

    nodes[idx].room = { roomX, roomY, roomW, roomH };

    for (int y = roomY; y < roomY + roomH; ++y)
    {
        for (int x = roomX; x < roomX + roomW; ++x)
        {
            if (map.inBounds(x, y))
            {
                map.at(x, y).terrain = Terrain::Floor;
            }
        }
    }

    // Assign starting position to the first placed leaf room
    if (map.startingPosition().x == 0 && map.startingPosition().y == 0)
    {
        map.setStartingPosition(getRoomCenter(nodes[idx].room));
    }
}

void MapGen::connectChildren(int idx, std::vector<BSPNode>& nodes, Map& map)
{
    int leftIdx = nodes[idx].left;
    int rightIdx = nodes[idx].right;

    if (leftIdx == -1 || rightIdx == -1) return;

    Point p1 = getRoomCenter(nodes[leftIdx].room);
    Point p2 = getRoomCenter(nodes[rightIdx].room);

   
    if (nodes[idx].room.w == 0)
    {
        nodes[idx].room = nodes[leftIdx].room;
    }

    createCorridor(map, p1, p2);
}

void MapGen::createCorridor(Map& map, Point p1, Point p2)
{
   
    Point curr = p1;

    while (curr.x != p2.x)
    {
        if (map.inBounds(curr)) map.at(curr).terrain = Terrain::Floor;
        curr.x += (p2.x > curr.x) ? 1 : -1;
    }

    while (curr.y != p2.y)
    {
        if (map.inBounds(curr)) map.at(curr).terrain = Terrain::Floor;
        curr.y += (p2.y > curr.y) ? 1 : -1;
    }

    if (map.inBounds(curr)) map.at(curr).terrain = Terrain::Floor;
}

Point MapGen::getRoomCenter(const SDL_Rect& rect)
{
    return { rect.x + rect.w / 2, rect.y + rect.h / 2 };
}