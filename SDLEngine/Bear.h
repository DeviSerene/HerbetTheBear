#pragma once
#include "Enemy.h"
class Bear :
	public Enemy
{
public:
	Bear();
	~Bear();
	void Draw(SpriteFactory* _sprite) override;
	void Update(PlayState* _state) override;
};