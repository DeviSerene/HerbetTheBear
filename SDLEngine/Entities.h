#pragma once
#include <SDL.h>
#include <string>
#include "SpriteFactory.h"
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
	virtual void Update();
	virtual void Draw(SpriteFactory* _sprite);
};

