#include "SpriteFactory.h"

SpriteFactory::SpriteFactory(SDL_Renderer* _renderer)
{
	m_renderer = _renderer; //the sprite factory now has a reference to the renderer, so it can create sprites
	m_spriteList.push_back(new Sprite(m_renderer, "base_0_0_1.bmp", 0,0, 84, 96)); //create an initial sprite
}

SpriteFactory::~SpriteFactory()
{
	//m_spriteList.clear();
	for (int i = 0; i < m_spriteList.size(); i++) //delete all sprites in memory
	{
		delete m_spriteList[i];
	}
	m_renderer = nullptr; //nullptr
}

void SpriteFactory::Draw(std::string _name, SDL_Rect _position) //for 'static' sprites
{
	GetSprite(_name, _position)->Draw();
}

void SpriteFactory::Draw(std::string _name, SDL_Rect _position, SDL_Rect& _cellRect) //the cellRect is used for animated sprites
{
	GetSprite(_name, _position)->AniDraw(_cellRect);
}

Sprite* SpriteFactory::GetSprite(std::string& _name, SDL_Rect& _position)
{
	for (int i = 0; i < m_spriteList.size(); i++) //look through our list of sprites, if it is in memory, use it
	{
		if (_name == m_spriteList[i]->GetName()) //we have found the sprite
		{
			m_spriteList[i]->SetPos(_position); //update the position of where we want to draw this
			return m_spriteList[i]; //return it
		}
	}

	//if it wasn't found then we need to add it
	CreateSprite(_name, _position);
	//and return this new sprite
	return m_spriteList[(m_spriteList.size()-1)];
}

void SpriteFactory::CreateSprite(std::string& _name, SDL_Rect& _position)
{
	//add a new sprite to memory
	m_spriteList.push_back(new Sprite(m_renderer, _name, _position.x, _position.y, _position.w, _position.h));
}