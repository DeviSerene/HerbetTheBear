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
	float cameraX, cameraY;

	bool drawnPlayer;

public:
	Entities();
	~Entities() {}

	virtual void Input() {}
	virtual void Update(PlayState* _state);
	virtual void Draw(SpriteFactory* _sprite) {}
	virtual bool CollideWith(Entities *_other);

	SDL_Rect getPosition() const { return EntityPosition; }
};

