#include "Player.h"



Player::Player()
	: Entities()
{
	EntityPosition.x = 100;
	EntityPosition.y = 100;
	EntityPosition.w = 
}


Player::~Player()
{

}

void Player::Input()
{

}

void Player::Update()
{

}

void Player::Draw(SpriteFactory *_sprite)
{
	_sprite->Draw(fileName, EntityPosition);
}

void Player::HandleDeath()
{

}

SDL_Rect Player::GetPlayerRect()
{
	return //rect;
}