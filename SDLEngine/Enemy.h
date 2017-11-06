#pragma once
#include "Entities.h"

class Enemy:
	public Entities
{
public:
	Enemy(float _speed);
	~Enemy();
	void Update();
protected:
	std::vector<SDL_Rect> destinations;
	size_t currentDest;
	float speed;
	bool flipped;
};