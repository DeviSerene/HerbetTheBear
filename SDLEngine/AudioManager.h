#pragma once
#include "Music.h"
#include "SoundEffect.h"
#include <vector>

class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	void MusicPlay(std::string _name);
	void MusicToggle();
	void MusicStop();
	void MusicLoad(std::string _name);
	void MusicClean();

	void SoundPlay(std::string _name, int _channel = -1);

private:

	Music* GetMusic(std::string& _name);
	SoundEffect* GetSound(std::string& _name); 
	void SoundLoad(std::string _name);

	std::vector <SoundEffect*> m_soundList;
	std::vector <Music*> m_musicList;
};

