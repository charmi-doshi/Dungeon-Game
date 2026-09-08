#pragma once
#include "Common.h"

struct Tile {
	Terrain terrain = Terrain::Wall;
	bool explored = false;
	bool visible = false;

	char glyph() const;
	SDL_Color  color() const;
};
