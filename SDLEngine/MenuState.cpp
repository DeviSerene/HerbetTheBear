#include "MenuState.h"
#include <string>
#include "PlayState.h"

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
	m_gameData->GetAudio()->MusicPlay("/assets/fft_trisection.mid");
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
				SDL_Rect r = SDL_Rect{ ev.button.x, ev.button.y, 1, 1 };
				int x = ev.button.x;
				int y = ev.button.y;

				if (x >= playRect.x && x < playRect.x + playRect.w && y >= playRect.y && y < playRect.y + playRect.h) {
					m_gameData->m_stateManager->ChangeState(new PlayState(m_gameData));
				}

				if (x >= exitRect.x && x < exitRect.x + exitRect.w && y >= exitRect.y && y < exitRect.y + exitRect.h) {
					m_gameData->m_stateManager->RemoveLastState();
					return false;
				}

				break;
			}
		case SDL_WINDOWEVENT:
			if (ev.window.event == SDL_WINDOWEVENT_CLOSE) {
				m_gameData->m_stateManager->RemoveLastState();
				return false;
			}
		}
	}
	return true;
}

void MenuState::Update(float _deltaTime)
{
	int width;
	int height;

	SDL_GetWindowSize(m_gameData->GetPlayerWindow(), &width, &height);
	playRect = { (width - 192) / 2, 300, 192, 64 };
	exitRect = { (width - 192) / 2, 400, 192, 64 };
}

void MenuState::Draw()
{
	int width;
	int height;

	SDL_GetWindowSize(m_gameData->GetPlayerWindow(), &width, &height);

	DrawText(m_gameData->GetHelperRenderer(), std::string("Please Press Play on Screen 1"), SDL_Color{255, 255, 255, 255 }, 10, 10);

	m_gameData->GetPlayerSprites()->Draw("assets/textures/PlayButton.png", playRect);
	m_gameData->GetPlayerSprites()->Draw("assets/textures/ExitButton.png", exitRect);

	m_gameData->GetPlayerSprites()->Draw("assets/KarstenHorse.png", { 200,100,50,50 });
	m_gameData->GetHelperSprites()->Draw("assets/KarstenHorse.png", { 200,100,50,50 });
}