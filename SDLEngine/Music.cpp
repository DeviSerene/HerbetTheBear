#include "Music.h"

Music::Music(std::string _name)
{
	//Load music
	m_name = _name;
	
	m_music = Mix_LoadMUS(_name.c_str());
	if (m_music == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
	}
}

Music::~Music()
{
	Mix_FreeMusic(m_music);
	m_music = NULL;
}

void Music::PlayMusic()
{
	if (Mix_PlayingMusic() == 0)
	{
		//Play the music
		Mix_PlayMusic(m_music, -1);
	}
	else
	{
		Mix_HaltMusic();
		Mix_PlayMusic(m_music, -1);
	}
}