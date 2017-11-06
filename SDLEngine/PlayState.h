#pragma once

#include "GameState.h"
#include "GameData.h"
#include "Enemy.h"

class TileMap;

class PlayState : public GameState
{
	float cameraX, cameraY;

public:

	TileMap* map;

	PlayState(GameData* data);
	~PlayState();
	virtual bool HandleSDLEvents();
	virtual void Update(float deltaTime);
	virtual void Draw();
	Enemy* enemy1;
};

