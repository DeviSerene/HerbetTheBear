#pragma once
#include "Enemy.h"
class Bear :
	public Enemy
{
public:
	~Bear();	
	Bear(PlayState * _state, SDL_Rect _wayPoints, bool _isPreset);
	void Init(PlayState* _state, SDL_Rect _wayPoints);
	void ReOrient(PlayState * _state);
	void Draw(SpriteFactory* _sprite) override;
	void Update(PlayState* _state, bool isPreset);
protected:
	SDL_Rect prevPos;
	int counter = 0;
	bool idle = false;
	int moveTime;
	bool isPreset;
	Timer animTimer;
};