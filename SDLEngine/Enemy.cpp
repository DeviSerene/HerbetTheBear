#include "Enemy.h"
#include <iostream>

Enemy::Enemy(float _speed)
{
	
	for (size_t i = 0; i < rand() % 10 + 2; i++)
	{
		SDL_Rect curr;
		//generate random positions
		curr.x = rand() % 800;
		curr.y = rand() % 800;
		destinations.push_back(curr);
		std::cout << curr.x << ", " << curr.y << std::endl;
	}
	EntityPosition = destinations.at(0);
	EntityPosition.w = EntityPosition.h = 32;
	currentDest = 0;
	speed = _speed;
}

Enemy::~Enemy()
{

}

void Enemy::Update()
{
	if ((EntityPosition.x != destinations.at(currentDest).x) || (EntityPosition.y != destinations.at(currentDest).y))
	{
		//Flip enemy to face towards destination
		if (EntityPosition.x > destinations.at(currentDest).x)
		{
			flipped = true;
		}
		else if (EntityPosition.x < destinations.at(currentDest).x)
		{
			flipped = false;
		}
		//move towards destination
		float deltaX = EntityPosition.x - destinations.at(currentDest).x;
		float deltaY = EntityPosition.y - destinations.at(currentDest).y;
		float distanceBetweenEntAndDest = std::sqrt(std::pow(deltaX, 2) + std::pow(deltaY, 2));
		EntityPosition.x -= round(deltaX / distanceBetweenEntAndDest);
		EntityPosition.y -= round(deltaY / distanceBetweenEntAndDest);
		//std::cout << deltaX / distanceBetweenEntAndDest << std::endl;
		//std::cout << EntityPosition.x << ", " << EntityPosition.y << ", Change: " << round(deltaX / distanceBetweenEntAndDest) + 1 << ", " << round(deltaY / distanceBetweenEntAndDest) + 1 << std::endl;
	}
	else
	{
		currentDest += 1;
	}
	if (currentDest == destinations.size())
	{
		currentDest = 0;
	}
	
}

void Enemy::Draw(SpriteFactory * _sprite)
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
	_sprite->Draw("assets/ghost_sheet.png", EntityPosition, cropRect , flipped);
}
