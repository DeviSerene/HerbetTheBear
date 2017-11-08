#include "MushroomSpike.h"

#include "SpriteFactory.h"
#include "PlayState.h"


MushroomSpike::MushroomSpike(int posX, int posY, bool decoy)
{
	EntityPosition.x = posX;
	EntityPosition.y = posY;
	EntityPosition.w = 64;
	EntityPosition.h = 64;
	hitboxWidth = 64;
	hitboxHeight = 32;
	this->decoy = decoy;
	revealed = false;
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
	_factory->Draw(decoy || !revealed ? MushroomSprite : SpikeSprite, EntityPosition, false, cameraX, cameraY);
}