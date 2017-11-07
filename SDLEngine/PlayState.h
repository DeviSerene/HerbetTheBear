#pragma once

#include "GameState.h"
#include "GameData.h"
#include "Player.h"
#include "SpriteFactory.h"
#include "Enemy.h"

class TileMap;


class PlayState : public GameState
{
public:
	float cameraX, cameraY;

	bool inputRight, inputLeft, inputUp;

	TileMap* map;
	Player* player;
	SpriteFactory* sprite;

	PlayState(GameData* data);
	~PlayState();
	virtual bool HandleSDLEvents();
	virtual void Update(float deltaTime);
	virtual void Draw();
	Enemy* enemy1;

};

