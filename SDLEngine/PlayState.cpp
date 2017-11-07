#include "PlayState.h"
#include "TileMap.h"
#include "GameData.h"
#include "Player.h"
#include "SpriteFactory.h"

PlayState::PlayState(GameData* _gameData) : GameState(_gameData)
	,cameraX(0), cameraY(0)
{
	enemy1 = new Enemy(10.0f);
	map = new TileMap(0, 0, 0, 0, "assets/textures/Forest_Tilesheet_01.png", "assets/maps/", "test.tmx");

	player = new Player();

	inputRight = false;
	inputLeft = false;
	inputUp = false;
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


	enemy1->Update(this);
	player->Update(this);
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

	
	
	map->Draw(m_gameData->GetPlayerSprites(), cameraX, cameraY, 6, playerW, playerH);
	map->Draw(m_gameData->GetHelperSprites(), cameraX, cameraY, 6, helperW, helperH);
	enemy1->Draw(m_gameData->GetHelperSprites());
	SDL_Rect playerPos = player->GetPlayerRect();
	playerPos.x = -cameraX + (playerPos.x);
	playerPos.y = -cameraY + (playerPos.y);

	m_gameData->GetPlayerSprites()->Draw("child_sheet.png", playerPos, player->GetPlayerCropRect(), player->getPlayerDirection());
	m_gameData->GetHelperSprites()->Draw("child_sheet.png", playerPos, player->GetPlayerCropRect(), player->getPlayerDirection());

}