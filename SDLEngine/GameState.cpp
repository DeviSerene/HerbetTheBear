#include "GameState.h"

GameState::GameState(GameData* _gamedata)
{
	m_gameData = _gamedata;
}

void GameState::DrawText(SDL_Renderer* _renderer, std::string& _text, SDL_Color _colour, int _x, int _y)
{
	_TTF_Font* font = TTF_OpenFont("assets/manaspc.ttf", 24); //font and fontsize

	SDL_Surface* surfaceText = TTF_RenderText_Solid(font, _text.c_str(), _colour);

	SDL_Texture* message = SDL_CreateTextureFromSurface(_renderer, surfaceText); //convert the surface into a texture

	SDL_Rect messageRect; //create a rect
	messageRect.x = _x; 
	messageRect.y = _y; 
	messageRect.w = surfaceText->w;
	messageRect.h = surfaceText->h;

	SDL_RenderCopy(_renderer, message, NULL, &messageRect); //send the text to the renderer

	SDL_FreeSurface(surfaceText); //free the surface
	surfaceText = nullptr;
	TTF_CloseFont(font);
	font = nullptr;
	SDL_DestroyTexture(message);
	message = nullptr;

}

int GameState::CheckKeyboardInput(SDL_Event& _ev)
{
	if (_ev.key.keysym.sym >= SDLK_a && _ev.key.keysym.sym <= SDLK_z)
	{
		return 1;
	}
	else if (_ev.key.keysym.sym == SDLK_BACKSPACE)
	{
		return 2;
	}
	else
	{
		return -1;
	}
}

std::string GameState::GetKeyboardLetter(SDL_Event& _ev)
{
	std::string ret; 
	ret += char(_ev.key.keysym.sym);
	return	ret;
}

void GameState::ChangeString(std::string& _change, bool _add, std::string _append, int _maxLength)
{
	if (_add)
	{
		if (!(_change.size() >= _maxLength-1)) 
		{
			//append the string with the new letter
			_change += _append;
		}
	}
	else
	{
		//we are deleting one letter
		if (_change.size() != 0) //check it isn't empty already
		{
			_change.pop_back();
		}
	}
}