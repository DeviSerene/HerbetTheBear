#pragma once

#include "GameState.h"
#include "GameData.h"
#include "Player.h"
#include "SpriteFactory.h"
#include "Ghost.h"
#include "Coin.h"

class TileMap;


class PlayState : public GameState
{
	std::vector<int> skyTiles;
	std::vector<Coin*> Coins;
	int coinx;
	int coiny;
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
	Ghost* ghost1;

};

