#pragma once

#include "GameState.h"
#include "GameData.h"

class TileMap;
class Player;
class SpriteFactory;

class PlayState : public GameState
{
	float cameraX, cameraY;

public:

	TileMap* map;
	Player* player;

	PlayState(GameData* data);
	~PlayState();
	virtual bool HandleSDLEvents();
	virtual void Update(float deltaTime);
	virtual void Draw();
};

