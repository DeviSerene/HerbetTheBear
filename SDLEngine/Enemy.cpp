#include "Enemy.h"
#include <iostream>
#include "PlayState.h"

Enemy::Enemy()
{	
	
	currentDest = 0;	
}

Enemy::~Enemy()
{

}

void Enemy::Update(PlayState* _state)
{
	Entities::Update(_state);
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
	}
	else
	{
		currentDest += 1;
	}
	if (currentDest == destinations.size())
	{
		currentDest = 0;
	}

	CollideWith(_state->player);
}

bool Enemy::CollideWith(Entities *_other) {
	if (Entities::CollideWith(_other)) {
		std::cout << "Collision!!";
		//Kill player or somit
	}
	return false;
}

void Enemy::Draw(SpriteFactory * _sprite)
{
	
}
