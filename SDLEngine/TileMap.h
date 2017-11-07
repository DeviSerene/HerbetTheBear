#pragma once

#include <vector>

#include "SpriteFactory.h"
#include "TMX/TMXMap.h"

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

	TMXTileSet* set;
public:

	TileMap(int _tileWidth, int _tileHeight, int _width, int _height, std::string _atlas, const char *_workingDir, const char *_level);
	~TileMap();

	void Collision(SDL_Rect& rect, float velX, float velY, bool& onGround);
	void Draw(SpriteFactory *_factory, float _cameraX, float _cameraY, int tileCountX, int _windowWidth, int _windowHeight);

	int getWidthInTiles() const { return width; }
	int getHeightInTiles() const { return height; }
};
