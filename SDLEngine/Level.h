#pragma once
#include <string>

struct Level 
{
	Level(std::string _TMXName, std::string _tileSet, int _tilesetWidth, std::string _backgroundTileSet, int _backgroundTilesetWidth) 
		: TMXName(_TMXName), tileSet(_tileSet), backgroundTileSet(_backgroundTileSet), tileSetWidth(_tilesetWidth), backgroundTileSetWidth(_backgroundTilesetWidth) {}
	Level() {}

	std::string TMXName;
	std::string tileSet;
	std::string backgroundTileSet;
	int tileSetWidth;
	int backgroundTileSetWidth;
	bool grass = true;
	std::vector<int> halfTileIndices;
};