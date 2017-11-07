#include "MenuState.h"

MenuState::MenuState(GameData* _gamedata)
	: GameState(_gamedata)
{
	
}

MenuState::~MenuState()
{
}

bool MenuState::HandleSDLEvents()
{
	//create an SDL event
	SDL_Event ev;
	int x, y;
	SDL_GetMouseState(&x, &y); //locate where the mouse is

	while (SDL_PollEvent(&ev))
	{
		switch (ev.type)
		{
		case SDL_QUIT: //player has pressed the X button
			m_gameData->m_stateManager->RemoveLastState();
			return false;
			break;
		case SDL_KEYDOWN:
			switch (ev.key.keysym.sym) //what key has been pressed?
			{
			case SDLK_ESCAPE:
				m_gameData->m_stateManager->RemoveLastState();
				return false;
				break;
			}
			break;

		case SDL_MOUSEBUTTONDOWN: //mouse button pressed
			switch (ev.button.button) //what key has been pressed?
			{
			case SDL_BUTTON_LEFT:
				break;
			}
			
		}
	}
	return true;
}

void MenuState::Update(float _deltaTime)
{

}

void MenuState::Draw()
{
	//DrawText(m_gameData->GetPlayerSprites(), "", SDL_Color{10, 10, 10, 10});
	m_gameData->GetPlayerSprites()->Draw("assets/KarstenHorse.png", { 200,100,50,50 });
	m_gameData->GetHelperSprites()->Draw("assets/KarstenHorse.png", { 200,100,50,50 });
}