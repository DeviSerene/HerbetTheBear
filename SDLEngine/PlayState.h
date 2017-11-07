#pragma once

#include "GameState.h"
#include "GameData.h"
#include "Player.h"
#include "SpriteFactory.h"
#include "Ghost.h"
#include "Coin.h"
#include "Bear.h"
#include "Timer.h"

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

	bool hasBeenHit;

	SDL_Rect doorPosRect;
	bool doorPosDetermined;
	SDL_Rect doorCropRect;
	bool doorSpawned;
	int doorIncrement;
	bool drawDoor;

	Timer DoorTimer;

public:
	float cameraX, cameraY;
	float delta;

	bool inputRight, inputLeft, inputUp;

	TileMap *map;
	Player *player;
	Clown *clown;
	SpriteFactory* sprite;

	PlayState(GameData* data);
	~PlayState();
	virtual bool HandleSDLEvents();
	virtual void Update(float deltaTime);
	virtual void Draw();
	std::vector<Ghost*> ghosts;
	std::vector<Bear*> bears;

	void nextLevel();
	void generateCoins(int _chance);
	void ScaleDoor();
};

