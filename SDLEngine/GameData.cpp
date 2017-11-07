#include "GameData.h"


GameData::GameData()
{
	m_lastTime = 0;
}


GameData::~GameData()
{
	delete m_audio;
	delete m_spritesPlayer;
	delete m_spritesHelper;
	SDL_DestroyRenderer(m_rendererPlayer);
	SDL_DestroyWindow(m_windowPlayer);
	SDL_DestroyRenderer(m_rendererHelper);
	SDL_DestroyWindow(m_windowHelper);
}

int GameData::Init(int _windowX, int _windowY)
{

	// try to create the window, log error and pause if fail
	m_windowPlayer = SDL_CreateWindow("GameJam - Player Window", 100, 100, _windowX, _windowY, SDL_WINDOW_SHOWN);
	if (m_windowPlayer == NULL)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		system("pause");
		return 0;
	}

	// try to create the renderer, log error and pause if fail
	m_rendererPlayer = SDL_CreateRenderer(m_windowPlayer, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_rendererPlayer == NULL)
	{
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		system("pause");
		return 0;
	}

	//HEPLER WINDOW
	m_windowHelper = SDL_CreateWindow("GameJam - Helper Window", _windowX+100, 100, _windowX, _windowY, SDL_WINDOW_SHOWN);
	if (m_windowHelper == NULL)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		system("pause");
		return 0;
	}

	// try to create the renderer, log error and pause if fail
	m_rendererHelper = SDL_CreateRenderer(m_windowHelper, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_rendererHelper == NULL)
	{
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		system("pause");
		return 0;
	}

	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		std::cout << "SDL_TTF could not initialize!";
		system("pause");
		return 0;
	}

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError();
		system("pause");
		return 0;
	}

	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		//system("pause");
		//return 0;
	}

	m_spritesPlayer = new SpriteFactory(m_rendererPlayer);
	m_spritesHelper = new SpriteFactory(m_rendererHelper);
	m_audio = new AudioManager();

	return 1;
}