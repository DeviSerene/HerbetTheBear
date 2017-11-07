#include "Bear.h"
#include "PlayState.h"

Bear::Bear(int _roamLeft, int _roamRight, int _height)
{
	destinations.push_back(SDL_Rect{ _roamLeft, _height, 64, 64 });
	destinations.push_back(SDL_Rect{ _roamRight, _height, 64, 64 });
	EntityPosition = destinations.at(0);
	EntityPosition.w = 64;
	EntityPosition.h = 63;
}

void Bear::Draw(SpriteFactory * _sprite)
{
	SDL_Rect cropRect;
	if (spriteIndex > 1)
	{
		spriteIndex = 0;
	}
	if (spriteIndex < 2)
	{
		cropRect.x = spriteIndex * 64;
		cropRect.y = 0;
		cropRect.w = cropRect.h = 64;
		spriteIndex += 1;
	}
	SDL_Rect worldPos = SDL_Rect{ EntityPosition.x - (int)cameraX, EntityPosition.y - (int)cameraY, EntityPosition.w, EntityPosition.h };
	_sprite->Draw("assets/textures/herbert.png", worldPos, cropRect, flipped);
}

void Bear::Update(PlayState * _state)
{
	Enemy::Update(_state);
	bool OnGround;
	int velX = 0;
	if (EntityPosition.x < destinations.at(currentDest).x)
	{
		velX = 1;
	}
	else if (EntityPosition.x > destinations.at(currentDest).x)
	{
		velX = -1;
	}
	else
	{
		currentDest += 1;
	}

	_state->map->Collision(EntityPosition, velX, 5, OnGround);
	//TODO: Add falling and ground collision
}
