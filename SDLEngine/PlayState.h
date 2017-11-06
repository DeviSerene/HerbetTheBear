#pragma once

#include "GameState.h"
#include "GameData.h"

class TileMap;

class PlayState : public GameState
{
public:

	TileMap* map;

	PlayState(GameData* data);
	~PlayState();
	virtual bool HandleSDLEvents();
	virtual void Update(float deltaTime);
	virtual void Draw();
};

