#pragma once
#include <SDL.h>
#include "Entities.h"
#include "TileMap.h"
#include "Timer.h"

class Player : public Entities
{

protected:

	SDL_Event key_input;

	//Crop Rect
	SDL_Rect CropRect;

	int playerHeath;
	bool playerDamaged;
	bool playerDead;
	bool invulnerabilityFrames;

	int numOfCoins;

	float volX;
	float volY;

	bool movingLeft;

	// Variables for handing Jumping
	bool playerJumping;
	bool playerFalling;
	bool onGround;
	int jumpLimit;
	int YBeforeJump;
	int LastFrameFallingPos;

	float timeLastFrame;
	float timeCurrentFrame;
	float deltaT;
	float frameTime;

	Timer animationTimer;
	Timer DamageOffsetTimer;

public:
	Player();
	~Player();

	void Input() override;
	void Update(PlayState* _state) override;
	void Draw(SpriteFactory *_sprite) override;
	bool CollideWith(Entities *_other) override;

	SDL_Rect GetPlayerRect();
	SDL_Rect GetPlayerCropRect();
	bool getPlayerDirection();
	void PlayerJump();
	int getPlayerHealth() const { return playerHeath; }
	void incrementCoins();
	int getCoins() const { return numOfCoins; }
	bool checkForPlayerDeath();
};

