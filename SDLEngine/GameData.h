#pragma once
#include <SDL.h>
#include <iostream>
#include <SDL_mixer.h>
#include <SDL_ttf.h> //text
#include <SDL_image.h> //images
#include "SpriteFactory.h"
#include "AudioManager.h"

class GamestateManager;

class GameData
{
public:
	GameData();
	~GameData();

	int Init(int _windowX, int _windowY);
	GamestateManager* m_stateManager;
	unsigned int GetLastTime() { return m_lastTime; }
	void SetLastTime(unsigned int _f) { m_lastTime = _f; }
	SDL_Renderer* GetPlayerRenderer() { return m_rendererPlayer; }
	SDL_Window* GetPlayerWindow() { return m_windowPlayer; }
	SDL_Renderer* GetHelperRenderer() { return m_rendererHelper; }
	SDL_Window* GetHelperWindow() { return m_windowHelper; }
	SpriteFactory* GetPlayerSprites() { return m_spritesPlayer; }
	SpriteFactory* GetHelperSprites() { return m_spritesHelper; }
	AudioManager* GetAudio() { return m_audio; }

private:

	AudioManager* m_audio;
	SpriteFactory* m_spritesPlayer;
	SpriteFactory* m_spritesHelper;
	SDL_Window* m_windowPlayer;
	SDL_Renderer* m_rendererPlayer;
	SDL_Window* m_windowHelper;
	SDL_Renderer* m_rendererHelper;
	unsigned int m_lastTime;
};

