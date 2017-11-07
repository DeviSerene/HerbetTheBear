#pragma once
#include "Enemy.h"

class Ghost:
	public Enemy
{
public:
	Ghost(int _xRange, int _yRange);
	~Ghost();
	void Update(PlayState * _state) override;
	void Draw(SpriteFactory* _sprite) override;

protected:
	
};