#pragma once
#include <SDL.h>
#include "Entities.h"

class Player : public Entities
{

protected:

	

public:
	Player();
	~Player();

	void Input() override ;
	void Update() override ;
	void Draw(SpriteFactory *_sprite) override;

	void HandleDeath();
	SDL_Rect GetPlayerRect();
};

