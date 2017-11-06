#pragma once

#include <vector>

#include "SpriteFactory.h"

class TileMap
{
private:
	//Size of each tile in pixels.
	int tileWidth;
	int tileHeight;
	//Width and height in tiles.
	int width;
	int height;
	
	std::vector<int> tileIndices;
	std::vector<TMXObjectGroup> mapObjects;
	std::string sprite;
public:

	TileMap(int _tileWidth, int _tileHeight, int _width, int _height, std::string _atlas, const char *_workingDir, const char *_level);
	~TileMap();
};

