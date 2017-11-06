#pragma once
#include <string>

struct TMXTileSet
{
	int tileWidth, tileHeight, tileCount, firstID;
	int imageWidth, imageHeight;
	int pixelFormat;
	unsigned char *imageData;
	std::string name;

	TMXTileSet(int tileWidth, int tileHeight, int tiles, int firstTileID, const char* name, const char* fileName);
	~TMXTileSet();
};

