#include "Player.h"
#include "PlayState.h"


Player::Player()
	: Entities()
{
	// stating players spawning position
	EntityPosition.x = 30;
	EntityPosition.y = 0;
	EntityPosition.w = 32;
	EntityPosition.h = 32;

	CropRect.x = 0;
	CropRect.y = 0;
	CropRect.w = 32;
	CropRect.h = 32;

	// Initilizing variables needed to handle player damage
	playerHeath = 3;
	playerHit = false;

	// initilizing the values needed to handle the player jumping
	playerFalling = false;
	playerJumping = false;
	jumpLimit = 40;

	timeLastFrame = 0.0f;
	frameTime - 0.0f;

	volX = 0;
	volY = 0;

	movingLeft = false;

	

}


Player::~Player()
{

}

void Player::Input()
{

}

void Player::Update(PlayState *_playState)
{
	timeLastFrame = timeCurrentFrame;
	timeCurrentFrame = SDL_GetTicks();
	deltaT = timeCurrentFrame - timeLastFrame;

	volX = 0;

	if (_playState->inputUp) {
		/*if (playerJumping == false)
		{
		playerJumping = true;
		// Initilizing this to allow the jump class to pair it with the jump limit while jumping
		YBeforeJump = EntityPosition.y;
		}*/

		volY = -10;
		movingLeft = true;
	}

	// Jump movement
	if (_playState->inputLeft) {
		// Left movement
		//EntityPosition.x -= 5;
		volX = -5;
		movingLeft = true;
		// Put sprite animation for left movement here
	} else if (_playState->inputRight) {
		volX = 5;
		movingLeft = false;
	}

	CropRect.x += 32;

	if (CropRect.x >= 128) {
		CropRect.x = 0;
	}

	volY += 1;
	if (volY > 5) volY = 5;
	Entities::Update(_playState);
	HandleDamage();

	bool onGround = false;
	_playState->map->Collision(EntityPosition, volX, volY, onGround);

	if (onGround) {
		if (volX > 0 || volX < 0) {
			CropRect.y = 32;
		}
		else {
			CropRect.y = 0;
		}
	}
	else {
		CropRect.y = 64;
	}

}

void Player::Draw(SpriteFactory *_sprite)
{
	// Draws the sprite
	_sprite->Draw(fileName, EntityPosition, CropRect, true);
}

void Player::HandleDamage()
{
	// This will be turned to true via a signal from the enemy class
	if (playerHit == true)
	{
		playerHeath -= 1;
		playerHit = false;
	}

	if (playerHeath == 0)
	{
		// Player dies
	}
}

SDL_Rect Player::GetPlayerRect()
{
	return EntityPosition;
}

SDL_Rect Player::GetPlayerCropRect()
{
	return CropRect;
}

bool Player::getPlayerDirection()
{
	return movingLeft;
}

void Player::PlayerJump()
{
	// player falling is false as long as the y axis is decreasing
	if (playerFalling == false)
	{
		if (EntityPosition.y > YBeforeJump - jumpLimit)
		{
			//EntityPosition.y -= 5;
			volY = -5;
		}
		else
		{
			// once the jump limit is reached, then we switch to player falling, and bring the lastframefallingpos into work to keep track of howe far the player can fall
			playerFalling = true;
			LastFrameFallingPos = EntityPosition.y;
			volY = 5;
			//EntityPosition.y += 5;
		}
	}

	// When player falling is true, this means the jump limit has been reached and it is ready to start falling
	else if (playerFalling == true)
	{
		// LastFrameFallingPos will always be equal to the entiry postion's y - 5 until the player hits something it can not move through e.g. the floor.
		if (LastFrameFallingPos != EntityPosition.y)
		{
			LastFrameFallingPos = EntityPosition.y;
			volY = 5;
			//EntityPosition.y += 5;
		}

		// This means the player has stopped falling due to an obsticle e.g. floor
		else if (LastFrameFallingPos == EntityPosition.y)
		{
			playerFalling = false;
			playerJumping = false;
		}
	}
}