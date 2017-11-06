#ifndef _GAMESTATE_
#define _GAMESTATE_

#include <SDL.h>
#include <iostream>
#include <string.h>
#include "SpriteFactory.h"
#include <SDL_ttf.h>
#include "GameData.h"

// forward declaration of GameStateManager
class GamestateManager;

class GameState {

public:
	GameState(GameData* _gamedata);

	//need this here to ensure inheriting class destructors will call properly
	virtual ~GameState() {}

	//any inheriting classes must provide these
	virtual bool HandleSDLEvents() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;

	std::string GetStateName() { return m_stateName; }

protected:
	std::string m_stateName;
	SDL_Rect m_tmp;
	GameData* m_gameData;
	virtual void DrawText(SDL_Renderer* _renderer, std::string& _text, SDL_Color _colour, int _x, int _y);

	bool MouseRect(int _x, int _y, SDL_Rect _rect)
	{
		if (_x >= _rect.x && _x <= (_rect.x + _rect.w) && _y >= _rect.y && _y <= (_rect.y + _rect.h))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	int GameState::CheckKeyboardInput(SDL_Event& _ev);
	std::string GetKeyboardLetter(SDL_Event& _ev);
	void ChangeString(std::string& _change, bool _add, std::string _append, int _maxLength);
};

#endif