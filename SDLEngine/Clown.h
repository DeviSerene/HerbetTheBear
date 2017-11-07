#pragma once

#include "Entities.h"

const char* ClownSprite = "assets/textures/evilClown.png";
const char* EvilChildSprite = "assets/textures/evilClownChild.png";
const char* NormalChildSprite = "assets/textures/normalClownChild.png";

enum class ClownState {
	Patrol,
	Attack
};

class Clown : public Entities
{
private:
	SDL_Rect crop;
	ClownState state;
	float startX;
	float endX;
	float targetX;
	bool decoy;
	float velX;
	float velY;
	bool onGround;
public:
	Clown(float posX, float posY, float patrolX, bool decoy);
	~Clown();

	virtual void Input() {}
	virtual void Update(PlayState* _state) override;
};

