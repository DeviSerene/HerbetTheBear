#include "Bear.h"
#include "PlayState.h"

Bear::Bear(PlayState* _state)
	: Enemy()
{
	Init(_state);
	hitboxWidth = 50;
	hitboxHeight = 40;
	animTimer = Timer(0.3f);
}

void Bear::Init(PlayState* _state)
{
	ReOrient(_state);
	EntityPosition = destinations.at(0);
	EntityPosition.w = 64;
	EntityPosition.h = 63;
	prevPos = EntityPosition;
	idle = false;
	moveTime = rand() % 500 + 150;
}

void Bear::ReOrient(PlayState* _state)
{
	destinations.clear();
	std::vector<SDL_Rect> topTiles = _state->map->getTopTiles();
	destinations.push_back(topTiles.at(rand() % topTiles.size()));
	destinations.push_back(topTiles.at(rand() % topTiles.size()));
	for (size_t i = 0; i < destinations.size(); i++)
	{
		destinations.at(i).x += 3;
		destinations.at(i).x *= 64;
		destinations.at(i).y *= 64 - 65;
	}
}

void Bear::Draw(SpriteFactory * _sprite)
{
	SDL_Rect cropRect;
	animTimer.Update(0.016f);
	if (animTimer.Completed()) {
		animTimer.Reset();
		spriteIndex++;
		if (spriteIndex > 1)
			spriteIndex = 0;
	}
	cropRect.x = spriteIndex * 64;
	cropRect.y = 0;
	cropRect.w = cropRect.h = 64;
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

	if (counter % 5 == 0 && (!idle))
	{
		if (EntityPosition.x == prevPos.x)
		{
			ReOrient(_state);			
		}
		prevPos = EntityPosition;
	}
	if (counter % moveTime == 0)
	{
		currentDest = 0;
		destinations.at(currentDest) = EntityPosition;
		for (size_t i = 1; i < destinations.size(); i++)
		{
			destinations.erase(destinations.begin() + i);
		}
		idle = true;
	}
	if (counter % (moveTime + moveTime / 2) == 0)
	{
		ReOrient(_state);
		idle = false;
		counter = 0;
	}

	counter++;
}
