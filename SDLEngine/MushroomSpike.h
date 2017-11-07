#pragma once

#include "Entities.h"

#define SpikeSprite "assets/textures/spike_helper.png"
#define MushroomSprite "assets/textures/spike.png"

class SpriteFactory;
class PlayState;

class MushroomSpike : public Entities
{
private:
	bool decoy, revealed;
public:
	MushroomSpike(int posX, int posY, bool decoy);
	~MushroomSpike();

	virtual void Input() {}
	virtual void Update(PlayState* _state) override;

	void DrawHelper(SpriteFactory *_factory, float cameraX, float cameraY);
	void DrawPlayer(SpriteFactory *_factory, float cameraX, float cameraY);

	bool isDecoy() const { return decoy; }
	void reveal() { revealed = true; }
};

