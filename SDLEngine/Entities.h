#pragma once
#include <SDL.h>
#include "SpriteFactory.h"
class Entities
{
public:
	Entities();
	~Entities();

	virtual void Input();
	virtual void Update();
	virtual void Draw(SpriteFactory* _sprite);
};

