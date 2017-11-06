#include "Player.h"

#include <iostream>


Player::Player()
	: Entities()
{
	// stating players spawning position
	EntityPosition.x = 100;
	EntityPosition.y = 150;
	EntityPosition.w = 100;
	EntityPosition.h = 100;

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
	timeCurrentFrame = 0.0f;
	frameTime - 0.0f;
	deltaT = 0.0f;

	movingLeft = false;



}


Player::~Player()
{

}

void Player::Input()
{
	std::cout << "Player pos y" << EntityPosition.y << std::endl;
	timeLastFrame = timeCurrentFrame;
	timeCurrentFrame = SDL_GetTicks();
	deltaT = (timeCurrentFrame - timeLastFrame) / 1000.0f;

	if (deltaT >= 0)
	{
		deltaT = 0;
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
					break;
					// Jump movement
				case SDLK_a:
					// Left movement
					EntityPosition.x -= 5;
					CropRect.y = 32;

					if (CropRect.x >= 128)
					{
						CropRect.x = 0;
					}
					std::cout << "Player pos x: " << EntityPosition.x << std::endl;
					std::cout << "Player pos y" << EntityPosition.y << std::endl;
					CropRect.x += 32;
					movingLeft = true;
					
					break;

					// Put sprite animation for left movement here

				case SDLK_d:

					//right movement
					EntityPosition.x += 5;
					CropRect.y = 32;

					if (CropRect.x >= 128)
					{
						CropRect.x = 0;
					}
					std::cout << "Player pos x: " << EntityPosition.x << std::endl;
					std::cout << "Player pos y" << EntityPosition.y << std::endl;
					CropRect.x += 32;
					movingLeft = false;

					break;

					// put sprite animation for right movement here

				}
			}
			else if (key_input.type == SDL_KEYUP)
			{
				CropRect.y = 0;

				if (CropRect.x >= 128)
				{
					CropRect.x = 0;
				}

				CropRect.x += 32;
			}

		}

		// While this is true, the player will be going through the jump cycle e.g Y axis increasing then decreasing
		if (playerJumping == true)
		{
			CropRect.y = 64;

			if (CropRect.x >= 128)
			{
				CropRect.x = 0;
			}

			CropRect.x += 32;
			PlayerJump();
			std::cout << "Crop rect x" << CropRect.x << std::endl;
		}
	}
}

void Player::Update()
{
	

	HandleDamage();
}

void Player::Draw(SpriteFactory *_sprite)
{
	// Draws the sprite
	//_sprite->Draw(fileName, EntityPosition, CropRect, true);
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
			EntityPosition.y -= 5;
		}
		else
		{
			// once the jump limit is reached, then we switch to player falling, and bring the lastframefallingpos into work to keep track of howe far the player can fall
			playerFalling = true;
			LastFrameFallingPos = EntityPosition.y;
			EntityPosition.y += 5;
		}
	}

	// When player falling is true, this means the jump limit has been reached and it is ready to start falling
	else if (playerFalling == true)
	{
		// LastFrameFallingPos will always be equal to the entiry postion's y - 5 until the player hits something it can not move through e.g. the floor.
		if (LastFrameFallingPos != EntityPosition.y)
		{
			LastFrameFallingPos = EntityPosition.y;
			EntityPosition.y += 5;
		}

		// This means the player has stopped falling due to an obsticle e.g. floor
		else if (LastFrameFallingPos == EntityPosition.y)
		{
			playerFalling = false;
			playerJumping = false;
		}
	}
}