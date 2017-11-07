#pragma once
#include "Enemy.h"
class Bear :
	public Enemy
{
public:
	~Bear();
	Bear(PlayState* _state);
	void Init(PlayState* _state);
	void Draw(SpriteFactory* _sprite) override;
	void Update(PlayState* _state) override;
};