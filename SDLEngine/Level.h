#pragma once
#include <string>

struct Level 
{
	Level(std::string _TMXName, std::string _tileSet, std::string _backgroundTileSet) : TMXName(_TMXName), tileSet(_tileSet), backgroundTileSet(_backgroundTileSet) {}
	Level() {}

	std::string TMXName;
	std::string tileSet;
	std::string backgroundTileSet;
};