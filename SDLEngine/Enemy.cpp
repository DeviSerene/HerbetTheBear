#include "Enemy.h"

Enemy::Enemy()
{
	srand(time_t(0));
	for (size_t i = 0; i < rand() % 5 + 2; i++)
	{
		SDL_Rect curr;
		//generate random positions
	}
	EntityPosition = destinations.at(0);
	currentDest = 0;
}

Enemy::~Enemy()
{

}

void Enemy::Update()
{
	if (EntityPosition.x != destinations.at(currentDest).x || EntityPosition.y != destinations.at(currentDest).y)
	{
		//move towards destination

	}
	else
	{
		currentDest += 1;
	}

}