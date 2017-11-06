#include "PlayState.h"
#include "TileMap.h"

PlayState::PlayState(GameData* _gameData) : GameState(_gameData)
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

	}

	return true;
}

void PlayState::Update(float deltaTime)
{
}

void PlayState::Draw()
{
	map->Draw(m_gameData->GetPlayerSprites(), 0, 0, 1);
	map->Draw(m_gameData->GetHelperSprites(), 0, 0, 1);
}