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
	//Flip enemy to face towards destination
		if (currentDest == destinations.size())
		{
			currentDest = 0;
		}
		if (EntityPosition.x > destinations.at(currentDest).x)
		{
			flipped = true;
		}
		else if (EntityPosition.x < destinations.at(currentDest).x)
		{
			flipped = false;
		}
		

	CollideWith(_state->player);
}

bool Enemy::CollideWith(Entities *_other) {
	if (Entities::CollideWith(_other)) {
		
		//Kill player or somit
	}
	return false;
}

void Enemy::Draw(SpriteFactory * _sprite)
{
	
}
