#include "AudioManager.h"

AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
	if (!m_musicList.empty())
	{
		for (int i = 0; i < m_musicList.size(); i++) //delete all in memory
		{
			delete m_musicList[i];
		}
	}
	if (!m_soundList.empty())
	{
		for (int i = 0; i < m_soundList.size(); i++) //delete all in memory
		{
			delete m_soundList[i];
		}
	}
}

void AudioManager::MusicPlay(std::string _name)
{
	GetMusic(_name)->PlayMusic();
}

Music* AudioManager::GetMusic(std::string& _name)
{
	if (!m_musicList.empty())
	{
		for (int i = 0; i < m_musicList.size(); i++) //look through our list, if it is in memory, use it
		{
			if (_name == m_musicList[i]->GetName()) //we have found
			{
				return m_musicList[i]; //return it
			}
		}
	}

	//if it wasn't found then we need to add it
	MusicLoad(_name);
	//and return this new
	return m_musicList[(m_musicList.size() - 1)];
}

void AudioManager::MusicLoad(std::string _name)
{
	m_musicList.push_back(new Music(_name));
}

void AudioManager::MusicToggle()
{
	if (Mix_PlayingMusic() == 1)
	{
		//If the music is paused
		if (Mix_PausedMusic() == 1)
		{
			//Resume the music
			Mix_ResumeMusic();
		}
		//If the music is playing
		else
		{
			//Pause the music
			Mix_PauseMusic();
		}
	}
}

void AudioManager::MusicStop()
{
	//Stop the music
	if (Mix_PlayingMusic() == 1)
		Mix_HaltMusic();
}

void AudioManager::MusicClean()
{
	if (!m_musicList.empty())
	{
		for (int i = 0; i < m_musicList.size(); i++) //delete all in memory
		{
			delete m_musicList[i];
		}
	}
}

void AudioManager::SoundPlay(std::string _name, int _channel)
{
	GetSound(_name)->PlaySound(_channel);
}

SoundEffect* AudioManager::GetSound(std::string& _name)
{
	if (!m_soundList.empty())
	{
		for (int i = 0; i < m_soundList.size(); i++) //look through our list, if it is in memory, use it
		{
			if (_name == m_soundList[i]->GetName()) //we have found
			{
				return m_soundList[i]; //return it
			}
		}
	}

	//if it wasn't found then we need to add it
	SoundLoad(_name);
	//and return this new
	return m_soundList[(m_soundList.size() - 1)];
}

void AudioManager::SoundLoad(std::string _name)
{
	m_soundList.push_back(new SoundEffect(_name));
}