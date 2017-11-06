#pragma once
#include <SDL.h>
#include <string>
#include "SpriteFactory.h"
#include "TileMap.h"
class Entities
{
protected:

	SDL_Rect EntityPosition;
	std::string fileName;

	bool drawnPlayer;

public:
	Entities();
	~Entities();

	virtual void Input();
	virtual void Update(TileMap *_tilemap);
	virtual void Draw(SpriteFactory* _sprite);
};

