#pragma once
#include <SDL.h>
#include "Sprite.h"
#include <vector>
#include <string>

class SpriteFactory //an organisational class that allows me to draw multiples of the same sprite, saving memory
{
public:
	SpriteFactory(SDL_Renderer* _renderer);
	~SpriteFactory();
	void Draw(std::string _name, SDL_Rect _position);
	void Draw(std::string _name, SDL_Rect _position, SDL_Rect& _cellRect); //two Draws, for static/animation
	Sprite* GetSprite(std::string& _name, SDL_Rect& _position); //return a sprite from the spritelist, or call Create Sprite
	void CreateSprite(std::string& _name, SDL_Rect& _position); //adds a sprite to spritelist

private:
	SDL_Renderer* m_renderer; //a reference to the renderer, for the creation of sprites
	std::vector <Sprite*> m_spriteList; //a list of all sprites in memory.
};

