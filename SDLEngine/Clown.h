#pragma once

#include "Entities.h"
#include "Timer.h"

#define ClownSprite "assets/textures/evilClown.png"
#define EvilChildSprite "assets/textures/evilClownChild.png"
#define NormalChildSprite "assets/textures/normalClownChild.png"
#define SmokeSprite "assets/textures/evilClown_smoke.png"

class Player;

enum class ClownState {
	Idle,
	Attack
};

class Clown : public Entities
{
private:
	ClownState state;
	float targetX;
	bool decoy;
	float velX;
	float velY;
	bool onGround;
	Player *player;
	bool flip;

	SDL_Rect animCrop;
	SDL_Rect smokeCrop;
	Timer animation;
	Timer smoke;

	bool inEvilRange;
public:
	Clown(float posX, float posY, float width, float height, Player *player, bool decoy);
	~Clown();

	virtual void Input() {}
	virtual void Update(PlayState* _state) override;

	void DrawHelper(SpriteFactory *_factory, float cameraX, float cameraY);
	void DrawPlayer(SpriteFactory *_factory, float cameraX, float cameraY);

	bool isDecoy() const { return decoy; }
};

