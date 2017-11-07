#include "Ghost.h"

Ghost::Ghost(int _xRange, int _yRange)
{
	
	for (size_t i = 0; i < rand() % 10 + 2; i++)
	{
		SDL_Rect curr;
		//generate random positions
		curr.x = rand() % _xRange;
		curr.y = rand() % _yRange;
		destinations.push_back(curr);
	}
	
	EntityPosition = destinations.at(0);
	EntityPosition.w = EntityPosition.h = 32;
}

Ghost::~Ghost()
{
}



void Ghost::Draw(SpriteFactory * _sprite)
{
	SDL_Rect cropRect;
	if (spriteIndex > 3)
	{
		spriteIndex = 0;
	}
	if (spriteIndex < 4)
	{
		cropRect.x = spriteIndex * 32;
		cropRect.y = 0;
		cropRect.w = cropRect.h = 32;
		spriteIndex += 1;
	}
	SDL_Rect worldPos = SDL_Rect{ EntityPosition.x - (int)cameraX, EntityPosition.y - (int)cameraY, EntityPosition.w, EntityPosition.h };
	_sprite->Draw("assets/textures/ghost_sheet.png", worldPos, cropRect, flipped);
}
