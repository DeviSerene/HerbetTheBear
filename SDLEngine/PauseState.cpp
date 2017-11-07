#include "PauseState.h"
#include "GamestateManager.h"

PauseState::PauseState(GameData *_gameData)
	:GameState(_gameData)
{
	strobeTimer = Timer(1.5f);
	strobe = true;
}


PauseState::~PauseState()
{

}

bool PauseState::HandleSDLEvents() {
	SDL_Event ev;
	while (SDL_PollEvent(&ev)) {
		if (ev.type == SDL_QUIT) {

		}
		else if (ev.type == SDL_KEYDOWN) {
			switch (ev.key.keysym.sym) {
			case SDLK_ESCAPE:
				m_gameData->m_stateManager->RemoveLastState();
				break;
			}
		}
	}
	return true;
}

void PauseState::Update(float deltaTime) {

}

void PauseState::Draw() {
	int playerWindowWidth, playerWindowHeight;
	int helperWindowWidth, helperWindowHeight;
	SDL_GetWindowSize(m_gameData->GetPlayerWindow(), &playerWindowWidth, &playerWindowHeight);
	SDL_GetWindowSize(m_gameData->GetHelperWindow(), &helperWindowWidth, &helperWindowHeight);
	m_gameData->GetPlayerSprites()->Draw("assets/textures/pause_overlay.png", SDL_Rect{ 0, 0, playerWindowWidth, playerWindowHeight });
	m_gameData->GetHelperSprites()->Draw("assets/textures/pause_overlay.png", SDL_Rect{ 0, 0, helperWindowWidth, helperWindowHeight });

	strobeTimer.Update(0.16f);
	if (strobeTimer.Completed()) {
		strobeTimer.Reset();
		strobe = !strobe;
	}
	if (strobe) {
		DrawText(m_gameData->GetHelperRenderer(), std::string("PAUSE"), SDL_Color{ 255, 255, 255 }, 30, 30);
		DrawText(m_gameData->GetPlayerRenderer(), std::string("PAUSE"), SDL_Color{ 255, 255, 255 }, 30, 30);
	}
}