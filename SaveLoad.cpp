#include "SaveLoad.h"
#include "MapGen.h"
#include <fstream>
#include <iostream>

bool SaveLoad::save(const Map& map, const Player& player, int depth, const std::string& path)
{
    std::ofstream f(path);
    if (!f.is_open()) return false;

    f << "v1\n";
    f << depth << "\n";

    // Access direct struct members from Entity.h
    f << player.x << " " << player.y << "\n";
    f << player.hp << " " << player.maxHp << "\n";

    // Write fog-of-war matrix using Map.h layout
    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < MAP_WIDTH; ++x)
        {
            f << (map.tiles[y][x].explored ? '1' : '0');
        }
        f << "\n";
    }

    return true;
}

bool SaveLoad::load(Map& map, Player& player, int& depth, const std::string& path)
{
    std::ifstream f(path);
    if (!f.is_open()) return false;

    std::string version;
    f >> version;
    if (version != "v1") return false;

    int px = 0, py = 0, hp = 0, maxHp = 0;
    f >> depth;
    f >> px >> py;
    f >> hp >> maxHp;

    // Regenerate layout using current dungeon depth
    MapGen::generate(map, depth);

    // Assign directly to Entity members
    player.x = px;
    player.y = py;
    player.hp = hp;
    player.maxHp = maxHp;

    // Restore saved fog-of-war matrix
    std::string line;
    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        f >> line;
        for (int x = 0; x < MAP_WIDTH && x < (int)line.length(); ++x)
        {
            map.tiles[y][x].explored = (line[x] == '1');
        }
    }

    return true;
}