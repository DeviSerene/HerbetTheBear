#pragma once
#include <SDL.h>
class Entities
{
public:
	Entities();
	~Entities();

	virtual void Input();
	virtual void Update();
	virtual void Draw(SDL_Renderer *_renderer);
};

