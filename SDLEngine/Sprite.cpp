#include "Sprite.h"

Sprite::Sprite(SDL_Renderer* _renderer, std::string _file, int _x, int _y, int _w, int _h)
{
	SDL_Surface* bmpFile = IMG_Load(_file.c_str()); //surface 
	m_image = SDL_CreateTextureFromSurface(_renderer, bmpFile); //texture is stored on a graphics card
	SDL_FreeSurface(bmpFile); //free the surface as we have a texture

	//assignments...
	m_name = _file;

	m_position.x = _x;
	m_position.y = _y;
	m_position.w = _w;
	m_position.h = _h;

	m_renderer = _renderer;
}


Sprite::~Sprite()
{
	if (m_image) //safety - ensure there is something to delete
		SDL_DestroyTexture(m_image); //free the memory
}

void Sprite::Draw()
{
	if (m_image)//safety - ensure there is something to draw
		SDL_RenderCopy(m_renderer, m_image, NULL, &m_position);
}

void Sprite::AniDraw(SDL_Rect& _cellRect)
{
	if (m_image)
		SDL_RenderCopy(m_renderer, m_image, &_cellRect, &m_position); 
}