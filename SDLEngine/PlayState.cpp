#include "PlayState.h"
#include "TileMap.h"
#include "GameData.h"
#include "Player.h"
#include "SpriteFactory.h"
#include "Teddy.h"

PlayState::PlayState(GameData* _gameData) : GameState(_gameData)
	,cameraX(0), cameraY(0)
{
	
	map = new TileMap(0, 0, 0, 0, "assets/textures/Forest_Tilesheet_01.png", "assets/maps/", "test.tmx");

	for (size_t i = 0; i < 36; i++)
	{
		ghosts.push_back(new Ghost(map->getWidthInTiles() * 64, map->getHeightInTiles() * 64));
	}
	bear = new Bear();

	skyTiles.resize(map->getWidthInTiles() * map->getHeightInTiles());
	for (int i = 0; i < skyTiles.size(); i++)
		skyTiles[i] = rand() % 3;

	player = new Player();

	inputRight = false;
	inputLeft = false;
	inputUp = false;

	teddy = new Teddy(SDL_Rect{ 64, 64, 32, 32 });
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
		} else if (event.type == SDL_KEYDOWN) {
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
			}
		} else if (event.type == SDL_KEYUP) {
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
	int playerW = 0, playerH = 0, helperW = 0, helperH = 0;
	SDL_GetWindowSize(m_gameData->GetPlayerWindow(), &playerW, &playerH);
	SDL_GetWindowSize(m_gameData->GetHelperWindow(), &helperW, &helperH);
	cameraX = player->GetPlayerRect().x - (playerW / 2);
	cameraY = player->GetPlayerRect().y - (playerH / 2);

	if(cameraX < 0)
		cameraX = 0;
	else if (cameraX > (map->getWidthInTiles() * 64) - playerW)
		cameraX = map->getWidthInTiles() * 64 - playerW;
	if (cameraY < 0)
		cameraY = 0;
	else if (cameraY > (map->getHeightInTiles() * 64) - playerH)
		cameraY = map->getHeightInTiles() * 64 - playerH;

	for (size_t i = 0; i < ghosts.size(); i++)
	{
		ghosts.at(i)->Update(this);
	}
	bear->Update(this);
	teddy->Update(this);
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
			m_gameData->GetPlayerSprites()->Draw("assets/textures/sky_sheet.png", SDL_Rect{ x * skySize - (int)cameraX, y * skySize - (int)cameraY, skySize, skySize }, SDL_Rect{ index * 64, 0, 64, 64 });
			m_gameData->GetHelperSprites()->Draw("assets/textures/sky_sheet.png", SDL_Rect{ x * skySize - (int)cameraX, y * skySize - (int)cameraY, skySize, skySize }, SDL_Rect{ index * 64, 0, 64, 64 });
		}
	}
	
	map->Draw(m_gameData->GetPlayerSprites(), cameraX, cameraY, 6, playerW, playerH);
	map->Draw(m_gameData->GetHelperSprites(), cameraX, cameraY, 6, helperW, helperH);
	for (size_t i = 0; i < ghosts.size(); i++)
	{
		ghosts.at(i)->Draw(m_gameData->GetHelperSprites());
	}
	bear->Draw(m_gameData->GetHelperSprites());
	SDL_Rect playerPos = player->GetPlayerRect();
	playerPos.x = -cameraX + (playerPos.x);
	playerPos.y = -cameraY + (playerPos.y);

	m_gameData->GetPlayerSprites()->Draw("child_sheet.png", playerPos, player->GetPlayerCropRect(), player->getPlayerDirection());
	m_gameData->GetHelperSprites()->Draw("child_sheet.png", playerPos, player->GetPlayerCropRect(), player->getPlayerDirection());

	teddy->Draw(m_gameData->GetHelperSprites());

	for (int i = 0; i < player->getPlayerHealth(); i++) {
		m_gameData->GetPlayerSprites()->Draw("assets/textures/heart.png", SDL_Rect{ 70 * i, playerH - 70, 64, 64 });
	}
}