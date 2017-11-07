#include "PlayState.h"
#include "TileMap.h"
#include "GameData.h"
#include "GamestateManager.h"
#include "Player.h"
#include "SpriteFactory.h"
#include "Teddy.h"
#include "Clown.h"
#include "Level.h"
#include "PauseState.h"

std::vector<int> forestHalfTiles = { 2, 4, 5, 8, 10, 11, 14, 16, 17, 20, 22, 23 };
std::vector<int> caveHalfTiles = { 3, 7 };
std::vector<int> circusHalfTiles = { 3, 4, 5 };

#define COIN_CHANCE 7
#define BEAR_MINIMUM 3
#define GHOST_COUNT 15

PlayState::PlayState(GameData* _gameData) : GameState(_gameData)
, cameraX(0), cameraY(0)
{
	currentLevel = 0;
	levels.resize(4);
	levels[0] = Level("test.tmx", "assets/textures/Forest_Tilesheet_01.png", 6, "assets/textures/sky_sheet.png", 3);
	levels[0].halfTileIndices = forestHalfTiles;

	levels[1] = Level("test_night.tmx", "assets/textures/Forest_Tilesheet_01.png", 6, "assets/textures/sky_sheet_dark.png", 3);
	levels[1].halfTileIndices = forestHalfTiles;

	levels[2] = Level("test_cave.tmx", "assets/textures/Cave_Tilesheet_01.png", 4, "assets/textures/cavebg_sheet.png", 3);
	levels[2].halfTileIndices = caveHalfTiles;

	levels[3] = Level("test_circus.tmx", "assets/textures/Circus_Tilesheet_01.png", 3, "assets/textures/circusbg_sheet.png", 3);
	levels[3].halfTileIndices = circusHalfTiles;
	levels[3].grass = false;

	map = new TileMap(0, 0, 0, 0, levels[currentLevel].tileSet.c_str(), "assets/maps/", levels[currentLevel].TMXName.c_str(), levels[currentLevel].halfTileIndices);



	for (size_t i = 0; i <= GHOST_COUNT; i++)
	{
		ghosts.push_back(new Ghost(map->getWidthInTiles() * 64, map->getHeightInTiles() * 64));
	}
	for (size_t j = 0; j < BEAR_MINIMUM; j++)
	{
		bears.push_back(new Bear(this));
	}
	skyTiles.resize(map->getWidthInTiles() * map->getHeightInTiles());
	for (int i = 0; i < skyTiles.size(); i++)
		skyTiles[i] = rand() % 3;

	player = new Player();

	inputRight = false;
	inputLeft = false;
	inputUp = false;

	generateCoins(COIN_CHANCE);

	teddy = new Teddy(map->teddyPos);

	clown = new Clown(400, 100, 32, 64, player, false);

	DoorTimer = Timer(2000.0);

	doorPosRect.w = 128;
	doorPosRect.h = 96;

	doorCropRect.x = doorCropRect.y = 0;
	doorCropRect.w = 128;
	doorCropRect.h = 96;

	drawDoor = false;
	doorPosDetermined = false;
	zoom = false;
}

PlayState::~PlayState()
{

}

bool PlayState::HandleSDLEvents()
{
	player->Input();

	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) {
			// Quit game
			//m_gameData->m_stateManager->RemoveLastState();
			return false;
		}
		else if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_SPACE:
			case SDLK_UP:
			case SDLK_w:
				inputUp = true;
				break;
			case SDLK_d:
			case SDLK_RIGHT:
				inputRight = true;
				break;
			case SDLK_a:
			case SDLK_LEFT:
				inputLeft = true;
				break;
			case SDLK_ESCAPE:
				m_gameData->m_stateManager->AddState(new PauseState(m_gameData));
				break;
			}
		}
		else if (event.type == SDL_KEYUP) {
			switch (event.key.keysym.sym) {
			case SDLK_SPACE:
			case SDLK_UP:
			case SDLK_w:
				inputUp = false;
				break;
			case SDLK_d:
			case SDLK_RIGHT:
				inputRight = false;
				break;
			case SDLK_a:
			case SDLK_LEFT:
				inputLeft = false;
				break;
			}
		}
	}

	return true;
}

void PlayState::Update(float deltaTime)
{
	this->delta = deltaTime;

	player->Update(this);
	for (int i = 0; i < Coins.size(); i++)
	{
		Coins[i]->Update(this);
	}
	int playerW = 0, playerH = 0, helperW = 0, helperH = 0;
	SDL_GetWindowSize(m_gameData->GetPlayerWindow(), &playerW, &playerH);
	SDL_GetWindowSize(m_gameData->GetHelperWindow(), &helperW, &helperH);
	cameraX = player->GetPlayerRect().x - (playerW / 2);
	cameraY = player->GetPlayerRect().y - (playerH / 2);

	if (cameraX < 0)
		cameraX = 0;
	else if (cameraX >(map->getWidthInTiles() * 64) - playerW)
		cameraX = map->getWidthInTiles() * 64 - playerW;
	if (cameraY < 0)
		cameraY = 0;
	else if (cameraY >(map->getHeightInTiles() * 64) - playerH)
		cameraY = map->getHeightInTiles() * 64 - playerH;

	for (size_t i = 0; i < ghosts.size(); i++)
	{
		ghosts.at(i)->Update(this);
		// Checking if player collides with any of the ghosts
		if (player->CollideWith(ghosts[i]))
		{
			player->playSoundEffect(m_gameData);
		}
	}

	// Calls the update function and checks if they player has collided with a coin, if so, coin disapears and the players coin count increases
	for (int i = 0; i < Coins.size(); i++)
	{
		Coins[i]->Update(this);
		Coins[i]->CollideWith(player);
		if (Coins[i]->getIfCoinDestroyed() == true)
		{
			//delete Coins.at(i);
			Coins.erase(Coins.begin() + i);
			player->incrementCoins();
			m_gameData->GetAudio()->SoundPlay("assets/sfx_coin.wav");
		}

	}
	player->Update(this);
	for (size_t i = 0; i < bears.size(); i++)
	{
		bears.at(i)->Update(this);
		// checking if the player is collisiding with any of the bears
		if (player->CollideWith(bears[i]))
		{
			player->playSoundEffect(m_gameData);
		}
	}
	teddy->Update(this);
	clown->Update(this);
	for (int i = 0; i < 20; i++)
	{
		if (player->CollideWith(clown))
		{
			player->playSoundEffect(m_gameData);
		}
	}

	if (teddy->CollideWith(player))
		drawDoor = true;


	// If this returns true, then the player has lost all of their lives and they lose
	if (player->checkForPlayerDeath() == true)
	{
		// Player dies, return to menu/end screen
	}
}

void PlayState::Draw()
{
	int playerW = 0, playerH = 0, helperW = 0, helperH = 0;
	SDL_GetWindowSize(m_gameData->GetPlayerWindow(), &playerW, &playerH);
	SDL_GetWindowSize(m_gameData->GetHelperWindow(), &helperW, &helperH);

	int skySize = 256;
	for (int x = 0; x < map->getWidthInTiles() / ((float)skySize / 64); x++) {
		for (int y = 0; y < map->getHeightInTiles() / ((float)skySize / 64); y++) {
			int index = skyTiles[(y * map->getWidthInTiles()) + x];
			m_gameData->GetPlayerSprites()->Draw(levels[currentLevel].backgroundTileSet, SDL_Rect{ x * skySize - (int)cameraX, y * skySize - (int)cameraY, skySize, skySize }, SDL_Rect{ index * 64, 0, 64, 64 });
			m_gameData->GetHelperSprites()->Draw(levels[currentLevel].backgroundTileSet, SDL_Rect{ x * skySize - (int)cameraX, y * skySize - (int)cameraY, skySize, skySize }, SDL_Rect{ index * 64, 0, 64, 64 });
		}
	}

	map->Draw(m_gameData->GetPlayerSprites(), cameraX, cameraY, levels[currentLevel].tileSetWidth, playerW, playerH, levels[currentLevel].grass);
	map->Draw(m_gameData->GetHelperSprites(), cameraX, cameraY, levels[currentLevel].tileSetWidth, helperW, helperH, levels[currentLevel].grass);
	for (size_t i = 0; i < ghosts.size(); i++)
	{
		ghosts.at(i)->Draw(m_gameData->GetHelperSprites());
	}
	for (int i = 0; i < Coins.size(); i++)
	{
		Coins[i]->Draw(m_gameData->GetPlayerSprites());
	}
	for (size_t i = 0; i < bears.size(); i++)
	{
		bears.at(i)->Draw(m_gameData->GetPlayerSprites());
	}
	SDL_Rect playerPos = player->GetPlayerRect();
	playerPos.x = -cameraX + (playerPos.x);
	playerPos.y = -cameraY + (playerPos.y);



	m_gameData->GetPlayerSprites()->Draw("child_sheet.png", playerPos, player->GetPlayerCropRect(), player->getPlayerDirection());
	m_gameData->GetHelperSprites()->Draw("child_sheet.png", playerPos, player->GetPlayerCropRect(), player->getPlayerDirection());

	teddy->Draw(m_gameData->GetHelperSprites());

	clown->DrawPlayer(m_gameData->GetPlayerSprites(), cameraX, cameraY);
	clown->DrawHelper(m_gameData->GetHelperSprites(), cameraX, cameraY);

	//UI
	m_gameData->GetPlayerSprites()->Draw("assets/textures/coin_sheet.png", SDL_Rect{ 30, 30, 32, 32 }, SDL_Rect{ 0, 0, 16, 16 });
	DrawText(m_gameData->GetPlayerRenderer(), std::to_string(player->getCoins()), SDL_Color{ 255, 255, 255 }, 62, 38);
	for (int i = 0; i < player->getPlayerHealth(); i++) {
		m_gameData->GetPlayerSprites()->Draw("assets/textures/heart.png", SDL_Rect{ 70 * i + 20, playerH - 70, 64, 64 });
	}

	if (drawDoor == true)
	{
		if (doorPosDetermined == false)
		{
			doorPosRect.x = playerPos.x - playerPos.w;
			doorPosRect.y = playerPos.y - 50;
			doorPosRect.w = 128;
			doorPosRect.h = 96;
			doorPosDetermined = true;
		}

		m_gameData->GetPlayerSprites()->Draw("assets/textures/Door_01.png", doorPosRect, doorCropRect);
		m_gameData->GetHelperSprites()->Draw("assets/textures/Door_01.png", doorPosRect, doorCropRect);

		zoom = true;
		ScaleDoor();


		/*if (DoorTimer.Completed())
		{
		nextLevel();
		drawDoor = false;
		doorPosDetermined = false;
		DoorTimer.Reset();
		}
		else
		{
		DoorTimer.Update(10);
		}*/
	}

}

void PlayState::nextLevel() {
	currentLevel++;
	if (currentLevel >= levels.size())
		currentLevel = 0;
	delete map;
	map = new TileMap(0, 0, 0, 0, levels[currentLevel].tileSet.c_str(), "assets/maps/", levels[currentLevel].TMXName.c_str(), levels[currentLevel].halfTileIndices);
	delete teddy;
	teddy = new Teddy(map->teddyPos);
	player->SetPlayerRect(SDL_Rect{ 30, 0, 32, 32 });
	generateCoins(COIN_CHANCE);

	for (size_t i = 0; i < bears.size(); i++)
	{
		bears.at(i)->Init(this);
	}
}

void PlayState::generateCoins(int _chance) {
	for (Coin *c : Coins)
		delete c;
	Coins.clear();
	for (SDL_Rect r : map->getTopTiles()) {
		if (rand() % _chance == 0) {
			Coin *c = new Coin();
			c->SetCoinPosRect(r.x * 64 + 24, r.y * 64 - 16);
			Coins.push_back(c);
		}
	}
}

void PlayState::ScaleDoor()
{
	//800 by 600
	if (zoom == true)
	{

		if (doorPosRect.x > 0)
		{
			doorPosRect.x -= 20;
		}


		if (doorPosRect.y > 0)
		{
			doorPosRect.y -= 22;

		}

		if (doorPosRect.w < 800)
		{
			doorPosRect.w += 20;
		}
		if (doorPosRect.h < 600)
		{
			doorPosRect.h += 20;
		}
	}

	if (doorPosRect.x < 0 && doorPosRect.y < 0 && doorPosRect.w > 800 && doorPosRect.h > 600)
	{
		// x = -2445
		// y = -3419
		// w = 5688
		// h = 5486

		doorPosRect.x -= 20;
		doorPosRect.y -= 28;
		doorPosRect.w += 40;
		doorPosRect.h += 40;
	}

	if (doorPosRect.x <= -2445 && doorPosRect.y <= -3419 && doorPosRect.w >= 5688 && doorPosRect.h >= 5486)
	{
		nextLevel();
		zoom = false;
		drawDoor = false;
		doorPosDetermined = false;
	}
}