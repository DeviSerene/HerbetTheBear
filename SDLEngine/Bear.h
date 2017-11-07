#pragma once
#include "Enemy.h"
class Bear :
	public Enemy
{
public:
	~Bear();
	Bear(int _roamLeft, int _roamRight, int _height);
	void Draw(SpriteFactory* _sprite) override;
	void Update(PlayState* _state) override;
};