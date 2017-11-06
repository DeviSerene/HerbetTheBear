#pragma once
#include <SDL_mixer.h>
#include <string>

class SoundEffect
{
public:
	SoundEffect(std::string _name);
	~SoundEffect();
	void PlaySound(int _channel = -1);
	std::string GetName() { return m_name; }
private:
	Mix_Chunk* m_sound = NULL;
	std::string m_name;
};

