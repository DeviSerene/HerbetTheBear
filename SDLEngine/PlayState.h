#pragma once

#include "GameState.h"
#include "GameData.h"

class PlayState : public GameState
{
public:
	PlayState(GameData* data);
	~PlayState();
	virtual bool HandleSDLEvents();
	virtual void Update(float deltaTime);
	virtual void Draw();
};

