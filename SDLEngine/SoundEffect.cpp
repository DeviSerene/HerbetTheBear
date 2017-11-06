#include "SoundEffect.h"



SoundEffect::SoundEffect(std::string _name)
{
	m_name = _name;
	m_sound = Mix_LoadWAV(_name.c_str());
	if (m_sound == NULL)
	{
		printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}

}

SoundEffect::~SoundEffect()
{
	Mix_FreeChunk(m_sound);
	m_sound = NULL;
}

void SoundEffect::PlaySound(int _channel)
{
	if (m_sound != NULL)
	{
		Mix_PlayChannel(_channel, m_sound, 0);
	}
}