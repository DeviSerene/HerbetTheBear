#include "Bear.h"

Bear::Bear()
{
	destinations.push_back(SDL_Rect{ 10, 520, 64, 64 });
	destinations.push_back(SDL_Rect{ 1000, 520, 64, 64 });
	EntityPosition = destinations.at(0);
	EntityPosition.w = EntityPosition.h = 64;
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
	//TODO: Add falling and ground collision
}
