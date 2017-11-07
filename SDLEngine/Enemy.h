#pragma once
#include "Entities.h"

class Enemy:
	public Entities
{
public:
	Enemy();
	~Enemy();
	void Update(PlayState* _state) override;
	void Draw(SpriteFactory* _sprite);
	bool CollideWith(Entities *_other) override;
protected:
	std::vector<SDL_Rect> destinations;
	size_t currentDest;
	bool flipped;
	int spriteIndex = 1;
};