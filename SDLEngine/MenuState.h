#pragma once
#include <SDL.h>
#include "GameState.h"
#include "GamestateManager.h"

class MenuState :
	public GameState
{
public:
	MenuState(GameData* _gamedata);				//constructor
	~MenuState();								//destructor

	bool HandleSDLEvents();						//handle inputs
	void Update(float _deltaTime);				//update 
	void Draw();								//draw to renderer
private:

};

