#include "Clown.h"
#include "PlayState.h"

Clown::Clown(float posX, float posY, float patrolX, bool _decoy)
	: startX(posX), endX(patrolX), decoy(_decoy)
{
	this->EntityPosition.x = posX;
	this->EntityPosition.y = posY;
	state = ClownState::Attack;
	velX = 0;
	velY = 0;
	targetX = patrolX;
}

Clown::~Clown()
{

}

void Clown::Update(PlayState* _state)
{
	velX = targetX - EntityPosition.x;
	velX = velX > 2 ? 2 : velX < -2 ? -2 : velX;

	velY += 0.75f;
	if (velY > 10) velY = 10;

	if (floorf(EntityPosition.x + velX) == floorf(targetX)) {
		if (floorf(targetX) == floorf(endX)) {
			targetX = startX;
		} else {
			targetX = endX;
		}
	}

	onGround = false;
	_state->map->Collision(EntityPosition, velX, velY, onGround);

	if (onGround) velY = 0;

}
