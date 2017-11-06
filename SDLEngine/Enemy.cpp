#include "Enemy.h"

Enemy::Enemy(float _speed)
{
	srand(time_t(0));
	for (size_t i = 0; i < rand() % 5 + 2; i++)
	{
		SDL_Rect curr;
		//generate random positions
	}
	EntityPosition = destinations.at(0);
	currentDest = 0;
	speed = _speed;
}

Enemy::~Enemy()
{

}

void Enemy::Update()
{
	if (EntityPosition.x != destinations.at(currentDest).x || EntityPosition.y != destinations.at(currentDest).y)
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
		int deltaX = EntityPosition.x - destinations.at(currentDest).x;
		int deltaY = EntityPosition.y - destinations.at(currentDest).y;
		int distanceBetweenEntAndDest = std::sqrt(std::pow(deltaX, 2) + std::pow(deltaY, 2));
		EntityPosition.x += deltaX / distanceBetweenEntAndDest * speed;
		EntityPosition.y += deltaY / distanceBetweenEntAndDest * speed;
	}
	else
	{
		currentDest += 1;
	}
	
}

void Enemy::Draw(SpriteFactory * _sprite)
{
	SDL_Rect cropRect;
	if (spriteIndex > 8)
	{
		spriteIndex = 1;
	}
	if (spriteIndex < 5)
	{
		cropRect.x = spriteIndex * 32;
		cropRect.y = 0;
		spriteIndex += 1;
	}
	else if (spriteIndex >= 5 && spriteIndex < 9)
	{
		cropRect.x = spriteIndex * 32;
		cropRect.y = spriteIndex;
		spriteIndex += 1;
	}
	_sprite->Draw("enemysprite.bmp", EntityPosition, cropRect, flipped);
}
