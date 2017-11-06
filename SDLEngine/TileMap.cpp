#include "TileMap.h"
#include "TMX\TMXMap.h"


TileMap::TileMap(int _tileWidth, int _tileHeight, int _width, int _height, std::string _atlas, const char *_workingDir, const char *_level)
	:tileWidth(_tileWidth), tileHeight(_tileHeight), width(_width), height(_height), sprite(_atlas)
{
	TMXMap map = TMXMap(_workingDir, _level);

}


TileMap::~TileMap()
{
}
