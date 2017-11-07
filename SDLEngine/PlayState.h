#pragma once

#include "GameState.h"
#include "GameData.h"
#include "Player.h"
#include "SpriteFactory.h"
#include "Ghost.h"
#include "Bear.h"

class TileMap;
class Teddy;

class PlayState : public GameState
{
	std::vector<int> skyTiles;
	Teddy *teddy;
public:
	float cameraX, cameraY;
	float delta;

	bool inputRight, inputLeft, inputUp;

	TileMap* map;
	Player* player;
	SpriteFactory* sprite;

	PlayState(GameData* data);
	~PlayState();
	virtual bool HandleSDLEvents();
	virtual void Update(float deltaTime);
	virtual void Draw();
	std::vector<Ghost*> ghosts;
	Bear* bear;

};

