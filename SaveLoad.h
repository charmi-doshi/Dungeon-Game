#pragma once

#include "Map.h"
#include "Player.h"
#include <string>

class SaveLoad
{
public:
    static bool save(const Map& map, const Player& player, int depth, const std::string& path = "savegame.dat");
    static bool load(Map& map, Player& player, int& depth, const std::string& path = "savegame.dat");
};