#pragma once

#include <vector>

#include "SpriteFactory.h"
#include "TMX/TMXMap.h"
#include "Timer.h"

struct TileFlags {
	bool top = true;
	bool left = true;
	bool right = true;
	bool bottom = true;
	bool halfTile = false;
};

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
	std::vector<TileFlags> tileFlags;
	std::vector<TMXObjectGroup> mapObjects;
	std::string sprite;

	int grassFrame;
	Timer grassTimer;

	TMXTileSet* set;
public:
	SDL_Rect teddyPos;

	TileMap(int _tileWidth, int _tileHeight, int _width, int _height, std::string _atlas, const char *_workingDir, const char *_level, std::vector<int> halfTiles = std::vector<int>());
	~TileMap();

	void Collision(SDL_Rect& rect, float velX, float velY, bool& onGround);
	void Draw(SpriteFactory *_factory, float _cameraX, float _cameraY, int tileCountX, int _windowWidth, int _windowHeight, bool grass);

	int getWidthInTiles() const { return width; }
	int getHeightInTiles() const { return height; }

	std::vector<SDL_Rect> getTopTiles() const;
};
