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
	float hitboxWidth;
	float hitboxHeight;
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

	inline SDL_Rect GetHitbox() {
		return SDL_Rect{ ((int)(EntityPosition.x + (EntityPosition.w / 2) - (hitboxWidth / 2)))
			, (int)((EntityPosition.y + EntityPosition.h) - hitboxHeight)
			, (int)hitboxWidth, (int)hitboxHeight };
	}

	SDL_Rect getPosition() const { return EntityPosition; }
};

