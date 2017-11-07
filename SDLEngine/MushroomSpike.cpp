#include "MushroomSpike.h"

#include "SpriteFactory.h"
#include "PlayState.h"


MushroomSpike::MushroomSpike(int posX, int posY, bool decoy)
{
	EntityPosition.x = posX;
	EntityPosition.y = posY;
	EntityPosition.w = 32;
	EntityPosition.h = 32;
	hitboxWidth = 32;
	hitboxHeight = 16;
	this->decoy = decoy;
}


MushroomSpike::~MushroomSpike()
{
}

void MushroomSpike::Update(PlayState* _state) {
}

void MushroomSpike::DrawHelper(SpriteFactory *_factory, float cameraX, float cameraY) {
	_factory->Draw(decoy ? MushroomSprite : SpikeSprite, EntityPosition, false, cameraX, cameraY);
}

void MushroomSpike::DrawPlayer(SpriteFactory *_factory, float cameraX, float cameraY) {
	_factory->Draw(MushroomSprite, EntityPosition, false, cameraX, cameraY);
}