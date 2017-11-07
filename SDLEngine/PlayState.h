#pragma once

#include "GameState.h"
#include "GameData.h"
#include "Player.h"
#include "SpriteFactory.h"
#include "Ghost.h"
#include "Coin.h"
#include "Bear.h"

class TileMap;
class Teddy;
class Clown;
struct Level;

class PlayState : public GameState
{
	std::vector<int> skyTiles;
	std::vector<Level> levels;
	Teddy *teddy;
	std::vector<Coin*> Coins;
	int coinx;
	int coiny;
	int currentLevel;
public:
	float cameraX, cameraY;
	float delta;

	bool inputRight, inputLeft, inputUp;

	TileMap *map;
	Player *player;
	Clown *clown;
	std::vector<Ghost*> ghosts;
	Bear* bear;
	SpriteFactory* sprite;

	PlayState(GameData* data);
	~PlayState();
	virtual bool HandleSDLEvents();
	virtual void Update(float deltaTime);
	virtual void Draw();
	void nextLevel();
};

