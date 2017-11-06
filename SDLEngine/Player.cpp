#include "Player.h"



Player::Player()
	: Entities()
{
	EntityPosition.x = 100;
	EntityPosition.y = 100;
	EntityPosition.w = 20;
	EntityPosition.h = 30;

	playerHeath = 3;
	playerHit = false;
	playerFalling = false;
	playerJumping = false;
	jumpLimit = 40;

}


Player::~Player()
{

}

void Player::Input()
{
	
	while (SDL_PollEvent(&key_input))
	{
		if (key_input.type == SDL_QUIT)
		{
			// Quit game
		}
		else if (key_input.type == SDL_KEYDOWN)
		{
			switch (key_input.key.keysym.sym)
			{
			case SDLK_SPACE:

				if (playerJumping == false)
				{
					playerJumping = true;
					// Initilizing this to allow the jump class to pair it with the jump limit while jumping
					YBeforeJump = EntityPosition.y;
				}
				// Jump movement
			case SDLK_a:

				EntityPosition.x -= 5;
				//left movement
			case SDLK_d:

				EntityPosition.x += 5;
				// right movement
			}
		}
	}

	if (playerJumping == true)
	{
		PlayerJump();
	}

}

void Player::Update()
{

}

void Player::Draw(SpriteFactory *_sprite)
{
	_sprite->Draw(fileName, EntityPosition);
}

void Player::HandleDamage()
{
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

void Player::PlayerJump()
{
	if (playerFalling == false)
	{
		if (EntityPosition.y > YBeforeJump - jumpLimit)
		{
			EntityPosition.y -= 5;
		}
		else
		{
			playerFalling = true;
			LastFrameFallingPos = EntityPosition.y;
			EntityPosition.y -= 5;
		}
	}
	else if (playerFalling == true)
	{
		if (LastFrameFallingPos != EntityPosition.y)
		{
			LastFrameFallingPos = EntityPosition.y;
			EntityPosition.y -= 5;
		}
		else if (LastFrameFallingPos == EntityPosition.y)
		{
			playerFalling = false;
			playerJumping = false;
		}
	}
}