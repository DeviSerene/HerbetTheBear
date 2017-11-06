#include "TMXTileSet.h"


TMXTileSet::TMXTileSet(int tileWidth, int tileHeight, int tiles, int firstTileID, const char* name, const char* fileName)
	:tileWidth(tileWidth), tileHeight(tileHeight), tileCount(tiles), firstID(firstTileID), name(name), imageWidth(0), imageHeight(0)
{
	//imageData = SOIL_load_image(fileName, &imageWidth, &imageHeight, &pixelFormat, SOIL_LOAD_AUTO);
}


TMXTileSet::~TMXTileSet()
{
}
