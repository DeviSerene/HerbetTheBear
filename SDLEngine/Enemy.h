#pragma once
#include "Entities.h"

class Enemy:
	public Entities
{
public:
	Enemy(float _speed);
	~Enemy();
	void Update(PlayState* _state) override;
	void Draw(SpriteFactory* _sprite);
protected:
	std::vector<SDL_Rect> destinations;
	size_t currentDest;
	float speed;
	bool flipped;
	int spriteIndex = 1;
};