#pragma once

#include "GameState.h"
#include "GameData.h"
#include "Player.h"
#include "SpriteFactory.h"
#include "Ghost.h"
#include "Coin.h"
#include "Bear.h"
#include "Timer.h"
#include "MenuState.h"

class TileMap;
class Teddy;
class Clown;
struct Level;
class MushroomSpike;

class PlayState : public GameState
{
	std::vector<int> skyTiles;
	std::vector<Level> levels;
	Teddy *teddy;
	std::vector<Coin*> Coins;
	int coinx;
	int coiny;
	int currentLevel;

	std::string _enemyType;

	bool hasBeenHit;

	SDL_Event mouse_clicked;

	SDL_Rect deathAnimationRect;
	SDL_Rect deathAnimationCropRect;

	SDL_Rect WinAnimationRect;
	SDL_Rect WinAnimationCropRect;

	SDL_Rect gameOverRect;
	SDL_Rect againRect;
	SDL_Rect youWinRect;

	int WindowSizeW;
	int WindowSizeH;

	SDL_Rect doorPosRect;
	bool doorPosDetermined;
	SDL_Rect doorCropRect;
	bool doorSpawned;
	int doorIncrement;
	bool drawDoor;
	bool hasWonGame;

	bool soundEffectPlayed;

	Timer DoorTimer;
	Timer DeathTimer;
	Timer WinTimer;
	bool zoom;

public:
	float cameraX, cameraY;
	float delta;

	bool inputRight, inputLeft, inputUp;

	TileMap *map;
	Player *player;
	std::vector<Clown*> clowns;
	std::vector<MushroomSpike*> spikes;
	SpriteFactory* sprite;

	PlayState(GameData* data);
	~PlayState();
	virtual bool HandleSDLEvents();
	virtual void Update(float deltaTime);
	virtual void Draw();
	std::vector<Ghost*> ghosts;
	std::vector<Bear*> bears;

	void nextLevel();
	void setLevel(int l);
	void generateCoins(int _chance);
	void ScaleDoor();
	void playDeathAnimation();
	void placeObjects();
	void WinScreen();
};

