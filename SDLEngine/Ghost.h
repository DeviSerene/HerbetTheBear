#pragma once
#include "Enemy.h"

class Ghost:
	public Enemy
{
public:
	Ghost(int _xRange, int _yRange);
	~Ghost();
	void Draw(SpriteFactory* _sprite) override;
protected:
	
};