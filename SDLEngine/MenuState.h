#pragma once
#include <SDL.h>
#include "GameState.h"
#include "GamestateManager.h"

#define BearLogo "assets/textures/Logo.png"

class MenuState :
	public GameState
{
public:
	SDL_Rect playRect;
	SDL_Rect exitRect;
	std::vector<int> randomBg;
	int bgW;
	int bgH;

	MenuState(GameData* _gamedata);				//constructor
	~MenuState();								//destructor

	bool HandleSDLEvents();						//handle inputs
	void Update(float _deltaTime);				//update 
	void Draw();								//draw to renderer

private:

};

