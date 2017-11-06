#include "PlayState.h"
#include "TileMap.h"

#include "Player.h"
#include "SpriteFactory.h"

PlayState::PlayState(GameData* _gameData) : GameState(_gameData)
	,cameraX(0), cameraY(0)
{
	map = new TileMap(0, 0, 0, 0, "assets/textures/grass.png", "assets/maps/", "test.tmx");
	enemy1 = new Enemy(10.0f);
	map = new TileMap(0, 0, 0, 0, "assets/textures/Forest_Tilesheet_01.png", "assets/maps/", "test.tmx");

	player = new Player();

}

PlayState::~PlayState()
{

}

bool PlayState::HandleSDLEvents()
{
	player->Input();

	return true;
}

void PlayState::Update(float deltaTime)
{

	
	player->Update(map);
	int playerW = 0, playerH = 0, helperW = 0, helperH = 0;
	SDL_GetWindowSize(m_gameData->GetPlayerWindow(), &playerW, &playerH);
	SDL_GetWindowSize(m_gameData->GetHelperWindow(), &helperW, &helperH);
	cameraX = player->GetPlayerRect().x - (playerW / 2);
	cameraY = player->GetPlayerRect().y - (playerH / 2);

}

void PlayState::Draw()
{
	int playerW = 0, playerH = 0, helperW = 0, helperH = 0;
	SDL_GetWindowSize(m_gameData->GetPlayerWindow(), &playerW, &playerH);
	SDL_GetWindowSize(m_gameData->GetHelperWindow(), &helperW, &helperH);

	map->Draw(m_gameData->GetPlayerSprites(), cameraX, cameraY, 1, playerW, playerH);
	map->Draw(m_gameData->GetHelperSprites(), cameraX, cameraY, 1, helperW, helperH);
	//enemy1->Draw(m_gameData->GetPlayerSprites());
	enemy1->Draw(m_gameData->GetHelperSprites());
	map->Draw(m_gameData->GetPlayerSprites(), cameraX, cameraY, 6, playerW, playerH);
	map->Draw(m_gameData->GetHelperSprites(), cameraX, cameraY, 6, helperW, helperH);
	
	SDL_Rect playerPos = player->GetPlayerRect();
	playerPos.x = -cameraX + (playerPos.x);
	playerPos.y = -cameraY + (playerPos.y);

	m_gameData->GetPlayerSprites()->Draw("child_sheet.png", playerPos, player->GetPlayerCropRect(), player->getPlayerDirection());

	m_gameData->GetHelperSprites()->Draw("child_sheet.png", playerPos, player->GetPlayerCropRect(), player->getPlayerDirection());

}