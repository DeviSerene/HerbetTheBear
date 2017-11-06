#include "PlayState.h"
#include "TileMap.h"

PlayState::PlayState(GameData* _gameData) : GameState(_gameData)
	,cameraX(0), cameraY(0)
{
	map = new TileMap(0, 0, 0, 0, "assets/textures/grass.png", "assets/maps/", "test.tmx");
}

PlayState::~PlayState()
{

}

bool PlayState::HandleSDLEvents()
{
	SDL_Event ev;

	while (SDL_PollEvent(&ev)) {
		switch (ev.type) {
		case SDL_KEYDOWN:
			switch (ev.key.keysym.sym) {
				
			}
			break;
		}
	}

	return true;
}

void PlayState::Update(float deltaTime)
{
}

void PlayState::Draw()
{
	int playerW = 0, playerH = 0, helperW = 0, helperH = 0;
	SDL_GetWindowSize(m_gameData->GetPlayerWindow(), &playerW, &playerH);
	SDL_GetWindowSize(m_gameData->GetHelperWindow(), &helperW, &helperH);

	map->Draw(m_gameData->GetPlayerSprites(), cameraX, cameraY, 1, playerW, playerH);
	map->Draw(m_gameData->GetHelperSprites(), cameraX, cameraY, 1, helperW, helperH);
}