#pragma once
#include <SDL.h>
#include "Entities.h"

class Player : public Entities
{

protected:

	SDL_Event key_input;

	SDL_Rect CropRect;

	int playerHeath;
	bool playerHit;

	bool movingLeft;

	// Variables for handing Jumping
	bool playerJumping;
	bool playerFalling;
	int jumpLimit;
	int YBeforeJump;
	int LastFrameFallingPos;

	float timeLastFrame;
	float timeCurrentFrame;
	float deltaT;
	float frameTime;

public:
	Player();
	~Player();

	void Input() override;
	void Update() override;
	void Draw(SpriteFactory *_sprite) override;

	void HandleDamage();
	SDL_Rect GetPlayerRect();
	void PlayerJump();
};

