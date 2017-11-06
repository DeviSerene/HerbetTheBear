#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Sprite
{
public:
	Sprite(SDL_Renderer* _renderer, std::string _file, int _x, int _y, int _w, int _h);
	~Sprite();

	void Draw();
	void AniDraw(SDL_Rect& _cellRect); //draw for animations

	std::string& GetName() { return m_name; } //used by SpriteFactory to locate sprites
	void SetPos(SDL_Rect _position) { m_position = _position; } //used by SpriteFactory to update the position

protected:
	SDL_Renderer* m_renderer; //sdl renderer used for drawing
	SDL_Texture* m_image; //a pointer to the image in memory
	SDL_Rect m_position; //where to draw this image

	std::string m_name;
};

