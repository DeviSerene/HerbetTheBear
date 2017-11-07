#include "Clown.h"
#include "PlayState.h"
#include "Player.h"

Clown::Clown(float posX, float posY, float width, float height, Player *player, bool _decoy) : decoy(_decoy), player(player)
{
	this->EntityPosition.x = posX;
	this->EntityPosition.y = posY;
	this->EntityPosition.w = width;
	this->EntityPosition.h = height;
	state = ClownState::Idle;
	velX = 0;
	velY = 0;
	inEvilRange = false;

	animation = Timer(0.125f);
	smoke = Timer(0.1f);

	animCrop = SDL_Rect{ 0, 0, 32, 64 };
	smokeCrop = SDL_Rect{ 128, 0, 32, 64 };

	hitboxWidth = 16;
	hitboxHeight = 46;
}

Clown::~Clown()
{

}

void Clown::Update(PlayState* _state)
{
	float distance = abs(hypotf(EntityPosition.x - player->getPosition().x, EntityPosition.y - player->getPosition().y));
	if (distance  < 50 && !decoy) {
		if (state == ClownState::Idle) {
			state = ClownState::Attack;
			smokeCrop.x = 0;
		}
	} else if (distance > 200 && !decoy) {
		if (state == ClownState::Attack) {
			state = ClownState::Idle;
			smokeCrop.x = 0;
		}
	}

	if (abs(player->getPosition().x - EntityPosition.x) < 100) {
		inEvilRange = true;
	}

	if (state == ClownState::Attack && !decoy) {
		velX = player->getPosition().x - EntityPosition.x;
		velX = velX > 3 ? 3 : velX < -3 ? -3 : velX;
	} else {
		velX = 0;
	}

	flip = velX < 0 ? true : velX > 0 ? false : flip;

	velY += 0.75f;
	if (velY > 10) velY = 10;

	onGround = false;
	_state->map->Collision(EntityPosition, velX, velY, onGround);

	if (onGround) velY = 0;

	animation.Update(_state->delta);
	smoke.Update(_state->delta);

	if (animation.Completed()) {
		animCrop.x += 32;

		if (animCrop.x >= 64)
			animCrop.x = 0;

		animation.Reset();
	}

	if (smoke.Completed()) {
		smokeCrop.x += 32;
		smoke.Reset();
	}

	if (state == ClownState::Idle) {
		animCrop.x = 0;
	}
}

void Clown::DrawHelper(SpriteFactory *_factory, float cameraX, float cameraY) {
	_factory->Draw(decoy ? NormalChildSprite : ClownSprite, EntityPosition, animCrop, flip, cameraX, cameraY);
}

void Clown::DrawPlayer(SpriteFactory *_factory, float cameraX, float cameraY) {
	_factory->Draw(state == ClownState::Attack ? ClownSprite : inEvilRange ? EvilChildSprite : NormalChildSprite, EntityPosition, animCrop, flip, cameraX, cameraY);
	_factory->Draw(SmokeSprite, EntityPosition, smokeCrop, flip, cameraX, cameraY);
}