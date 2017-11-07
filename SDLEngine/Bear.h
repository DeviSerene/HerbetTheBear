#pragma once
#include "Enemy.h"
class Bear :
	public Enemy
{
public:
	~Bear();
	Bear(PlayState* _state);
	Bear(PlayState* _state, SDL_Rect wayPoints);
	void Init(PlayState* _state);
	void ReOrient(PlayState * _state);
	void Draw(SpriteFactory* _sprite) override;
	void Update(PlayState* _state, bool isPreset);
protected:
	SDL_Rect prevPos;
	int counter = 0;
	bool idle = false;
	int moveTime;
	Timer animTimer;
};