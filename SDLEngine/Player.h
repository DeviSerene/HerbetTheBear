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

	int numOfCoins;
	bool playerHit;

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

public:
	Player();
	~Player();

	void Input() override;
	void Update(PlayState* _state) override;
	void Draw(SpriteFactory *_sprite) override;

	void HandleDamage();
	SDL_Rect GetPlayerRect();
	void SetPlayerRect(SDL_Rect _rect) { EntityPosition = _rect; }
	SDL_Rect GetPlayerCropRect();
	bool getPlayerDirection();
	void PlayerJump();
	int getPlayerHealth() const { return playerHeath; }
	void incrementCoins();
	int getCoins() const { return numOfCoins; }
};

