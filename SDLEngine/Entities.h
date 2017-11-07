#pragma once
#include <SDL.h>
#include <string>
#include "SpriteFactory.h"
#include "TileMap.h"

class PlayState;

class Entities
{
protected:

	SDL_Rect EntityPosition;
	std::string fileName;

	bool drawnPlayer;

public:
	Entities();
	~Entities() {}

	virtual void Input() {}
	virtual void Update(PlayState* _state) {}
	virtual void Draw(SpriteFactory* _sprite) {}
};

