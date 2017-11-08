#include "PlayState.h"
#include "TileMap.h"
#include "GameData.h"
#include "GamestateManager.h"
#include "Player.h"
#include "SpriteFactory.h"
#include "Teddy.h"
#include "Clown.h"
#include "Level.h"
#include "PauseState.h"
#include "MushroomSpike.h"

std::vector<int> forestHalfTiles = { 2, 4, 5, 8, 10, 11, 14, 16, 17, 20, 22, 23 };
std::vector<int> caveHalfTiles = { 3, 7 };
std::vector<int> circusHalfTiles = { 3, 4, 5 };

#define COIN_CHANCE 300
#define BEAR_MINIMUM 2
#define GHOST_COUNT 30
#define FREEZE_AI false

PlayState::PlayState(GameData* _gameData) : GameState(_gameData)
, cameraX(0), cameraY(0)
{
	currentLevel = 0;
	levels.resize(4);
	levels[0] = Level("Forest.tmx", "assets/textures/Forest_Tilesheet_01.png", 6, "assets/textures/sky_sheet_dark.png", 3);
	levels[0].halfTileIndices = forestHalfTiles;
	levels[3] = Level("Stairwell.tmx", "assets/textures/Cave_Tilesheet_01.png", 4, "assets/textures/cavebg_sheet.png", 3);
	levels[3].halfTileIndices = caveHalfTiles;
	levels[2] = Level("level_caves.tmx", "assets/textures/Cave_Tilesheet_01.png", 4, "assets/textures/cavebg_sheet.png", 3);
	levels[2].halfTileIndices = caveHalfTiles;
	levels[1] = Level("ToTheCircus.tmx", "assets/textures/Circus_Tilesheet_01.png", 3, "assets/textures/circusbg_sheet.png", 3);
	levels[1].halfTileIndices = caveHalfTiles;
	levels[1].grass = false;

	map = new TileMap(0, 0, 0, 0, levels[currentLevel].tileSet.c_str(), "assets/maps/", levels[currentLevel].TMXName.c_str(), levels[currentLevel].halfTileIndices);

	player = new Player();
	placeObjects();
	for (size_t i = 0; i <= GHOST_COUNT; i++)
	{
		ghosts.push_back(new Ghost(map->getWidthInTiles() * 64, map->getHeightInTiles() * 64));
	}
	for (size_t j = 0; j < BEAR_MINIMUM; j++)
	{
		bears.push_back(new Bear(this, SDL_Rect{ 0, 0, 0, 0 }, false));
	}
	skyTiles.resize(map->getWidthInTiles() * map->getHeightInTiles());
	for (int i = 0; i < skyTiles.size(); i++)
		skyTiles[i] = rand() % 3;

	SDL_GetWindowSize(m_gameData->GetPlayerWindow(), &WindowSizeW, &WindowSizeH);

	inputRight = false;
	inputLeft = false;
	inputUp = false;

	teddy = new Teddy(map->teddyPos);

	DoorTimer = Timer(2000.0);
	DeathTimer = Timer(100.0);
	WinTimer = Timer(100.0);

	doorPosRect.w = 128;
	doorPosRect.h = 96;

	doorCropRect.x = doorCropRect.y = 0;
	doorCropRect.w = 128;
	doorCropRect.h = 96;

	drawDoor = false;
	doorPosDetermined = false;
	zoom = false;

	soundEffectPlayed = false;

	deathAnimationRect.w = 200;
	deathAnimationRect.h = 200;
	deathAnimationRect.x = (WindowSizeW / 2) - deathAnimationRect.w / 2;
	deathAnimationRect.y = (WindowSizeH / 2) - deathAnimationRect.h / 2;

	deathAnimationCropRect.x = deathAnimationCropRect.y = 0;

	WinAnimationRect.w = 200;
	WinAnimationRect.h = 200;
	WinAnimationRect.x = (WindowSizeW / 2) - WinAnimationRect.w / 2;
	WinAnimationRect.y = (WindowSizeH / 2) - WinAnimationRect.h / 2;

	WinAnimationCropRect.x = WinAnimationCropRect.y = 0;

	
	gameOverRect.w = 352;
	gameOverRect.h = 320;
	gameOverRect.x = (WindowSizeW / 2) - gameOverRect.w / 2;
	gameOverRect.y = (WindowSizeH / 2) - gameOverRect.h;
	

	againRect.w = 496;
	againRect.h = 128;
	againRect.x = (WindowSizeW / 2) - againRect.w / 2;
	againRect.y = (WindowSizeH / 2) + againRect.h;

	youWinRect.w = 256;
	youWinRect.h = 224;
	youWinRect.x = (WindowSizeW / 2) - youWinRect.w / 2;
	youWinRect.y = (WindowSizeH / 2) - youWinRect.h;

	hasWonGame = false;

	musicStopped = false;
	musicChanged = false;
	
}

PlayState::~PlayState()
{

}

bool PlayState::HandleSDLEvents()
{
	player->Input();

	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) {
			// Quit game
			//m_gameData->m_stateManager->RemoveLastState();
			return false;
		}
		else if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_SPACE:
			case SDLK_UP:
			case SDLK_w:
				inputUp = true;
				break;
			case SDLK_d:
			case SDLK_RIGHT:
				inputRight = true;
				break;
			case SDLK_a:
			case SDLK_LEFT:
				inputLeft = true;
				break;
			case SDLK_ESCAPE:
				m_gameData->m_stateManager->AddState(new PauseState(m_gameData));
				break;
			case SDLK_1:
				setLevel(0);
				break;
			case SDLK_2:
				setLevel(1);
				break;
			case SDLK_3:
				setLevel(2);
				break;
			case SDLK_4:
				setLevel(3);
				break;
			case SDLK_5:
				setLevel(4);
				break;
			case SDLK_6:
				setLevel(5);
				break;
			case SDLK_7:
				setLevel(6);
				break;
			case SDLK_8:
				setLevel(7);
				break;
			case SDLK_9:
				setLevel(8);
				break;
			}
		}
		else if (event.type == SDL_KEYUP) {
			switch (event.key.keysym.sym) {
			case SDLK_SPACE:
			case SDLK_UP:
			case SDLK_w:
				inputUp = false;
				break;
			case SDLK_d:
			case SDLK_RIGHT:
				inputRight = false;
				break;
			case SDLK_a:
			case SDLK_LEFT:
				inputLeft = false;
				break;
			}

		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				if (!hasWonGame && !player->checkForPlayerDeath())
					continue;
				int x = event.button.x;
				int y = event.button.y;

				if (x >= againRect.x && x < againRect.x + againRect.w && y >= againRect.y && y < againRect.y + againRect.h) {
					m_gameData->m_stateManager->ChangeState(new MenuState(m_gameData));
					soundEffectPlayed = false;
				}
				if (x >= youWinRect.x && x < youWinRect.x + youWinRect.w && y >= youWinRect.y && y < youWinRect.y + youWinRect.h)
				{
					m_gameData->m_stateManager->ChangeState(new MenuState(m_gameData));
					soundEffectPlayed = false;
				}
			}
		}
		if(event.type == SDL_WINDOWEVENT) {
			if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
				m_gameData->m_stateManager->ClearStates();
				return false;
			}
		}
	}

	return true;
}

void PlayState::Update(float deltaTime)
{
	if (musicChanged == false)
	{
		if (currentLevel == 0)
		{
			if (musicStopped == false)
			{
				m_gameData->GetAudio()->MusicStop();
				//m_gameData->GetAudio()->MusicClean();
				musicStopped = true;
				
			}
			//m_gameData->GetAudio()->MusicLoad("assets/bgm_forest.mp3");
			m_gameData->GetAudio()->MusicPlay("assets/The_Caves.mid");
			musicChanged = true;
		}
		else if (currentLevel == 1)
		{
			if (musicStopped == false)
			{
				m_gameData->GetAudio()->MusicStop();
				//m_gameData->GetAudio()->MusicClean();
				musicStopped = true;
			}
			//m_gameData->GetAudio()->MusicLoad("assets/bgm_circus.mp3");
			m_gameData->GetAudio()->MusicPlay("assets/Clockwork_Mansion.mid");
			musicChanged = true;
		}
		else if (currentLevel == 2)
		{
			if (musicStopped == false)
			{
				m_gameData->GetAudio()->MusicStop();
				//m_gameData->GetAudio()->MusicClean();
				musicStopped = true;
			}
			//m_gameData->GetAudio()->MusicLoad("assets/bgm_cave.mp3");
			m_gameData->GetAudio()->MusicPlay("assets/The_Waterfalls.mid");
			musicChanged = true;
		}
	}
	this->delta = deltaTime;
	if (hasWonGame == false && !drawDoor)
	{
		if (player->checkForPlayerDeath() == false)
		{
			player->Update(this);
			for (int i = 0; i < Coins.size(); i++)
			{
				Coins[i]->Update(this);
			}
			int playerW = 0, playerH = 0, helperW = 0, helperH = 0;
			SDL_GetWindowSize(m_gameData->GetPlayerWindow(), &playerW, &playerH);
			SDL_GetWindowSize(m_gameData->GetHelperWindow(), &helperW, &helperH);
			cameraX = player->GetPlayerRect().x - (playerW / 2);
			cameraY = player->GetPlayerRect().y - (playerH / 2);

			if (cameraX < 0)
				cameraX = 0;
			else if (cameraX > (map->getWidthInTiles() * 64) - playerW)
				cameraX = map->getWidthInTiles() * 64 - playerW;
			if (cameraY < 0)
				cameraY = 0;
			else if (cameraY > (map->getHeightInTiles() * 64) - playerH)
				cameraY = map->getHeightInTiles() * 64 - playerH;

			if (player->checkForPlayerDeath() == false)
			{
				for (size_t i = 0; i < ghosts.size(); i++)
				{
					ghosts.at(i)->Update(this);
					// Checking if player collides with any of the ghosts
					if (!FREEZE_AI && player->CollideWith(ghosts[i]))
					{
						player->playSoundEffect(m_gameData);
					}
					if (player->checkForPlayerDeath())
					{
						_enemyType = "Ghost";
					}
				}
			}

			// Calls the update function and checks if they player has collided with a coin, if so, coin disapears and the players coin count increases
			for (int i = 0; i < Coins.size(); i++)
			{
				Coins[i]->Update(this);
				Coins[i]->CollideWith(player);
				if (Coins[i]->getIfCoinDestroyed() == true)
				{
					//delete Coins.at(i);
					Coins.erase(Coins.begin() + i);
					player->incrementCoins();
					m_gameData->GetAudio()->SoundPlay("assets/sfx_coin.wav");
				}

			}

			if (player->checkForPlayerDeath() == false)
			{
				for (int i = 0; i < spikes.size(); i++)
				{
					spikes[i]->Update(this);
					if (!FREEZE_AI && spikes[i]->isDecoy() == false)
					{
						if (player->CollideWith(spikes[i]))
						{
							player->playSoundEffect(m_gameData);
						}
						if (player->checkForPlayerDeath())
						{
							_enemyType = "Spikes";
						}
					}
				}
			}

			player->Update(this);
			if (player->checkForPlayerDeath() == false)
			{
				for (size_t i = 0; i < bears.size(); i++)
				{
					bears.at(i)->Update(this);
					// checking if the player is collisiding with any of the bears
					if (!FREEZE_AI && player->CollideWith(bears[i]))
					{
						player->playSoundEffect(m_gameData);

					}
					if (player->checkForPlayerDeath())
					{
						_enemyType = "Bear";
					}
				}
			}
			teddy->Update(this);
			if (player->checkForPlayerDeath() == false)
			{
				for (Clown *c : clowns)
				{
					c->Update(this);
					if (c->isDecoy() == false)
					{
						if (!FREEZE_AI && player->CollideWith(c))
						{
							player->playSoundEffect(m_gameData);
						}
						if (player->checkForPlayerDeath())
						{
							_enemyType = "Clown";
						}
					}

				}
			}

			if (teddy->CollideWith(player))
				drawDoor = true;

		}
	}
	
	
}

void PlayState::Draw()
{
	if (hasWonGame == false)
	{
		if (player->checkForPlayerDeath() == false)
		{
			int playerW = 0, playerH = 0, helperW = 0, helperH = 0;
			SDL_GetWindowSize(m_gameData->GetPlayerWindow(), &playerW, &playerH);
			SDL_GetWindowSize(m_gameData->GetHelperWindow(), &helperW, &helperH);

			int skySize = 256;
			for (int x = 0; x < map->getWidthInTiles() / ((float)skySize / 64); x++) {
				for (int y = 0; y < map->getHeightInTiles() / ((float)skySize / 64); y++) {
					int index = skyTiles[(y * map->getWidthInTiles()) + x];
					m_gameData->GetPlayerSprites()->Draw(levels[currentLevel].backgroundTileSet, SDL_Rect{ x * skySize - (int)cameraX, y * skySize - (int)cameraY, skySize, skySize }, SDL_Rect{ index * 64, 0, 64, 64 });
					m_gameData->GetHelperSprites()->Draw(levels[currentLevel].backgroundTileSet, SDL_Rect{ x * skySize - (int)cameraX, y * skySize - (int)cameraY, skySize, skySize }, SDL_Rect{ index * 64, 0, 64, 64 });
				}
			}

			map->Draw(m_gameData->GetPlayerSprites(), cameraX, cameraY, levels[currentLevel].tileSetWidth, playerW, playerH, levels[currentLevel].grass);
			map->Draw(m_gameData->GetHelperSprites(), cameraX, cameraY, levels[currentLevel].tileSetWidth, helperW, helperH, levels[currentLevel].grass);
			for (size_t i = 0; i < ghosts.size(); i++)
			{
				ghosts.at(i)->Draw(m_gameData->GetHelperSprites());
			}
			for (int i = 0; i < Coins.size(); i++)
			{
				Coins[i]->Draw(m_gameData->GetPlayerSprites());
			}
			for (size_t i = 0; i < bears.size(); i++)
			{
				bears.at(i)->Draw(m_gameData->GetPlayerSprites());
				bears.at(i)->Draw(m_gameData->GetHelperSprites());
			}
			SDL_Rect playerPos = player->GetPlayerRect();
			playerPos.x = -cameraX + (playerPos.x);
			playerPos.y = -cameraY + (playerPos.y);



			m_gameData->GetPlayerSprites()->Draw("assets/textures/child_sheet.png", playerPos, player->GetPlayerCropRect(), player->getPlayerDirection());
			m_gameData->GetHelperSprites()->Draw("assets/textures/child_sheet.png", playerPos, player->GetPlayerCropRect(), player->getPlayerDirection());

			teddy->Draw(m_gameData->GetHelperSprites());

			for (Clown *c : clowns) {
				c->DrawPlayer(m_gameData->GetPlayerSprites(), cameraX, cameraY);
				c->DrawHelper(m_gameData->GetHelperSprites(), cameraX, cameraY);
			}

			//UI
			for (int i = 0; i < player->getPlayerHealth(); i++) {
				m_gameData->GetPlayerSprites()->Draw("assets/textures/heart.png", SDL_Rect{ 70 * i + 20, playerH - 70, 64, 64 });
			}

			for (MushroomSpike* spike : spikes) {
				spike->DrawHelper(m_gameData->GetHelperSprites(), cameraX, cameraY);
				spike->DrawPlayer(m_gameData->GetPlayerSprites(), cameraX, cameraY);
			}

			if (drawDoor == true)
			{
				if (doorPosDetermined == false)
				{
					doorPosRect.x = playerPos.x - playerPos.w;
					doorPosRect.y = playerPos.y - 50;
					doorPosRect.w = 128;
					doorPosRect.h = 96;
					doorPosDetermined = true;
				}

				m_gameData->GetPlayerSprites()->Draw("assets/textures/Door_01.png", doorPosRect, doorCropRect);
				m_gameData->GetHelperSprites()->Draw("assets/textures/Door_01.png", doorPosRect, doorCropRect);

				zoom = true;
				ScaleDoor();


				if (DoorTimer.Completed())
				{
					nextLevel();
					drawDoor = false;
					doorPosDetermined = false;
					DoorTimer.Reset();
				}
				else
				{
					DoorTimer.Update(10);
				}
			}
		}
		else if (player->checkForPlayerDeath() == true)
		{
			playDeathAnimation();
		}
	}
	else if (hasWonGame == true)
	{
		WinScreen();
	}

	

}

void PlayState::setLevel(int _l) {
	currentLevel = _l;
	musicStopped = false;
	musicChanged = false;
	if (currentLevel >= levels.size())
	{
		currentLevel = levels.size() - 1;
	}
	else if (currentLevel < 0) {
		currentLevel = 0;
	}
	delete map;
	map = new TileMap(0, 0, 0, 0, levels[currentLevel].tileSet.c_str(), "assets/maps/", levels[currentLevel].TMXName.c_str(), levels[currentLevel].halfTileIndices);
	delete teddy;
	teddy = new Teddy(map->teddyPos);
	placeObjects();

	for (size_t i = 0; i < bears.size(); i++)
	{
		bears.at(i)->Init(this, SDL_Rect{ 0, 0, 0, 0 });
	}
}

void PlayState::nextLevel() {
	currentLevel++;
	if (currentLevel >= levels.size())
	{
		hasWonGame = true;
		return;
		
	}
	delete map;
	map = new TileMap(0, 0, 0, 0, levels[currentLevel].tileSet.c_str(), "assets/maps/", levels[currentLevel].TMXName.c_str(), levels[currentLevel].halfTileIndices);
	delete teddy;
	teddy = new Teddy(map->teddyPos);
	placeObjects();

	for (size_t i = 0; i < bears.size(); i++)
	{
		bears.at(i)->Init(this, SDL_Rect{ 0, 0, 0, 0 });
	}
}

void PlayState::placeObjects() {
	for (Clown *c : clowns)
		delete c;
	clowns.clear();

	for (MushroomSpike *ms : spikes)
		delete ms;
	spikes.clear();

	for (Bear *b : bears)
		delete b;
	bears.clear();

	for (Coin *c : Coins)
		delete c;
	Coins.clear();

	for (TMXObject *ob : map->getObjects()[0]->objects) {
		if (ob->name == "Child_Decoy")
			clowns.push_back(new Clown(ob->x - 16, ob->y - 64, 32, 64, player, true));
		else if (ob->name == "Child_Clown")
			clowns.push_back(new Clown(ob->x - 16, ob->y - 64, 32, 64, player, false));
		else if (ob->name == "Mushroom")
			spikes.push_back(new MushroomSpike(ob->x, ob->y, true));
		else if (ob->name == "Spike")
			spikes.push_back(new MushroomSpike(ob->x, ob->y, false));
		else if (ob->name == "Waypoint")
			bears.push_back(new Bear(this, SDL_Rect{ ob->x, ob->y, ob->width, ob->height }, true));
		else if (ob->name == "Player")
			player->SetPlayerRect(SDL_Rect{ ob->x, ob->y - 32, 32, 32 });
		else if (ob->name == "Heart") {
			Coin *c = new Coin();
			c->SetCoinPosRect(ob->x, ob->y);
			Coins.push_back(c);
		}
	}

	if (Coins.size() <= 0)
		generateCoins(COIN_CHANCE);
}

void PlayState::generateCoins(int _chance) {
	for (Coin *c : Coins)
		delete c;
	Coins.clear();
	for (SDL_Rect r : map->getTopTiles()) {
		if (rand() % _chance < 10 - player->getPlayerHealth()) {
			Coin *c = new Coin();
			c->SetCoinPosRect(r.x * 64 + 24, r.y * 64 - 16);
			Coins.push_back(c);
		}
	}
}

void PlayState::ScaleDoor()
{
	player->setInvincibility(true);
	//800 by 600
	if (zoom == true)
	{

		if (doorPosRect.x > 0)
		{
			doorPosRect.x -= 40;
		}


		if (doorPosRect.y > 0)
		{
			doorPosRect.y -= 44;

		}

		if (doorPosRect.w < WindowSizeW)
		{
			doorPosRect.w += 60;
		}
		if (doorPosRect.h < WindowSizeH)
		{
			doorPosRect.h += 40;
		}
	}

	if (doorPosRect.x < 0 && doorPosRect.y < 0 && doorPosRect.w > WindowSizeW && doorPosRect.h > WindowSizeH)
	{
		// x = -2445
		// y = -3419
		// w = 5688
		// h = 5486

		doorPosRect.x -= 40;
		doorPosRect.y -= 56;
		doorPosRect.w += 80;
		doorPosRect.h += 80;
	}

	if (doorPosRect.x <= -2445 && doorPosRect.y <= -3419 && doorPosRect.w >= 5688 && doorPosRect.h >= 5486)
	{
		nextLevel();
		zoom = false;
		drawDoor = false;
		doorPosDetermined = false;
		player->setInvincibility(false);
		musicStopped = false;
		musicChanged = false;
	}
}

void PlayState::playDeathAnimation()
{
	if (_enemyType == "Clown")
	{
		
		m_gameData->GetPlayerSprites()->Draw("assets/textures/ClownDeath_TileSet_01.png", deathAnimationRect, deathAnimationCropRect);
		m_gameData->GetHelperSprites()->Draw("assets/textures/ClownDeath_TileSet_01.png", deathAnimationRect, deathAnimationCropRect);
		m_gameData->GetPlayerSprites()->Draw("assets/textures/AgainButton.png", againRect);
		m_gameData->GetHelperSprites()->Draw("assets/textures/AgainButton.png", againRect);
		m_gameData->GetPlayerSprites()->Draw("assets/textures/GameOver.png", gameOverRect);
		m_gameData->GetHelperSprites()->Draw("assets/textures/GameOver.png", gameOverRect);
		m_gameData->GetAudio()->MusicStop();
		m_gameData->GetAudio()->SoundPlay("assets/sfx_clown.wav");
		// Play clown death animation
		
		if (DeathTimer.Completed())
		{
			DeathTimer.Reset();
			deathAnimationCropRect.w = 64;
			deathAnimationCropRect.h = 64;
			if (deathAnimationCropRect.x != 64 || deathAnimationCropRect.y != 192)
			{
				deathAnimationCropRect.x += 64;
				if (deathAnimationCropRect.x >= 320)
				{
					deathAnimationCropRect.x = 0;
					deathAnimationCropRect.y += 64;
				}
			}
			else if (deathAnimationCropRect.x == 36 && deathAnimationCropRect.y == 192)
			{
				// Call back to menu or lose state
				
				HandleSDLEvents();
			}
		}
		else
		{
			DeathTimer.Update(10);
		}

	}
	else if (_enemyType == "Ghost")
	{
		// play ghost death animation

		m_gameData->GetPlayerSprites()->Draw("assets/textures/GhostDeath_TileSet_01.png", deathAnimationRect, deathAnimationCropRect);
		m_gameData->GetHelperSprites()->Draw("assets/textures/GhostDeath_TileSet_01.png", deathAnimationRect, deathAnimationCropRect);
		m_gameData->GetPlayerSprites()->Draw("assets/textures/AgainButton.png", againRect);
		m_gameData->GetHelperSprites()->Draw("assets/textures/AgainButton.png", againRect);
		m_gameData->GetPlayerSprites()->Draw("assets/textures/GameOver.png", gameOverRect);
		m_gameData->GetHelperSprites()->Draw("assets/textures/GameOver.png", gameOverRect);
		
		if (soundEffectPlayed == false)
		{
			m_gameData->GetAudio()->MusicStop();
			m_gameData->GetAudio()->SoundPlay("assets/sfx_slurp.wav", 1);
			soundEffectPlayed = true;
		}
		// play bear death animation
		if (DeathTimer.Completed())
		{
			DeathTimer.Reset();
			deathAnimationCropRect.w = 64;
			deathAnimationCropRect.h = 64;
			// Play clown death animation


			if (deathAnimationCropRect.x != 256 || deathAnimationCropRect.y != 192)
			{
				deathAnimationCropRect.x += 64;
				if (deathAnimationCropRect.x >= 320)
				{
					deathAnimationCropRect.x = 0;
					deathAnimationCropRect.y += 64;
				}
			}
			else if (deathAnimationCropRect.x == 256 && deathAnimationCropRect.y == 192)
			{

			
				HandleSDLEvents();
				// Call back to menu or lose state
			}
		}
		else
		{
			DeathTimer.Update(10);
		}
	}
	else if(_enemyType == "Spikes")
	{
		// play spikes death animation

		m_gameData->GetPlayerSprites()->Draw("assets/textures/SpikeDeath_TileSet_01.png", deathAnimationRect, deathAnimationCropRect);
		m_gameData->GetHelperSprites()->Draw("assets/textures/SpikeDeath_TileSet_01.png", deathAnimationRect, deathAnimationCropRect);
		m_gameData->GetPlayerSprites()->Draw("assets/textures/AgainButton.png", againRect);
		m_gameData->GetHelperSprites()->Draw("assets/textures/AgainButton.png", againRect);
		m_gameData->GetPlayerSprites()->Draw("assets/textures/GameOver.png", gameOverRect);
		m_gameData->GetHelperSprites()->Draw("assets/textures/GameOver.png", gameOverRect);
		if (soundEffectPlayed == false)
		{
			m_gameData->GetAudio()->MusicStop();
			m_gameData->GetAudio()->SoundPlay("assets/sfx_spikeImpale.wav", 1);
			soundEffectPlayed = true;
		}
		// play bear death animation
		if (DeathTimer.Completed())
		{
			DeathTimer.Reset();
			deathAnimationCropRect.w = 64;
			deathAnimationCropRect.h = 64;
			// Play clown death animation

			if (deathAnimationCropRect.x != 256 || deathAnimationCropRect.y != 192)
			{
				deathAnimationCropRect.x += 64;
				if (deathAnimationCropRect.x >= 320)
				{
					deathAnimationCropRect.x = 0;
					deathAnimationCropRect.y += 64;
				}
			}
			else if (deathAnimationCropRect.x == 256 && deathAnimationCropRect.y == 192)
			{
				
				HandleSDLEvents();
				// Call back to menu or lose state
				
			}
		}
		else
		{
			DeathTimer.Update(10);
		}
	}
	else if (_enemyType == "Bear")
	{
		m_gameData->GetPlayerSprites()->Draw("assets/textures/BearDeath_TileSet_01.png", deathAnimationRect, deathAnimationCropRect);
		m_gameData->GetHelperSprites()->Draw("assets/textures/BearDeath_TileSet_01.png", deathAnimationRect, deathAnimationCropRect);
		m_gameData->GetPlayerSprites()->Draw("assets/textures/AgainButton.png", againRect);
		m_gameData->GetHelperSprites()->Draw("assets/textures/AgainButton.png", againRect);
		m_gameData->GetPlayerSprites()->Draw("assets/textures/GameOver.png", gameOverRect);
		m_gameData->GetHelperSprites()->Draw("assets/textures/GameOver.png", gameOverRect);

		if (soundEffectPlayed == false)
		{
			m_gameData->GetAudio()->MusicStop();
			m_gameData->GetAudio()->SoundPlay("assets/sfx_bear.wav", 1);
			soundEffectPlayed = true;
		}
		// play bear death animation
		if (DeathTimer.Completed())
		{
			DeathTimer.Reset();
			deathAnimationCropRect.w = 64;
			deathAnimationCropRect.h = 64;
			// Play clown death animation
			

			if (deathAnimationCropRect.x != 256 || deathAnimationCropRect.y != 192)
			{
				deathAnimationCropRect.x += 64;
				if (deathAnimationCropRect.x >= 320)
				{
					deathAnimationCropRect.x = 0;
					deathAnimationCropRect.y += 64;
				}
			}
			else if (deathAnimationCropRect.x == 256 && deathAnimationCropRect.y == 192)
			{
				
				HandleSDLEvents();
				// Call back to menu or lose state
			}
		}
		else
		{
			DeathTimer.Update(10);
		}
	}
	
}

void PlayState::WinScreen()
{
	m_gameData->GetPlayerSprites()->Draw("assets/textures/win_TileSet.png", WinAnimationRect, WinAnimationCropRect);
	m_gameData->GetHelperSprites()->Draw("assets/textures/win_TileSet.png", WinAnimationRect, WinAnimationCropRect);
	m_gameData->GetPlayerSprites()->Draw("assets/textures/YouWin.png", youWinRect);
	m_gameData->GetHelperSprites()->Draw("assets/textures/YouWin.png", youWinRect);

	if (soundEffectPlayed == false)
	{
		m_gameData->GetAudio()->MusicStop();
		m_gameData->GetAudio()->SoundPlay("assets/sfx_bear.wav");
	}

	if (WinTimer.Completed())
	{
		WinTimer.Reset();
		WinAnimationCropRect.w = 64;
		WinAnimationCropRect.h = 64;


		if (WinAnimationCropRect.x != 192 || WinAnimationCropRect.y != 0)
		{
			WinAnimationCropRect.x += 64;

		}
		else if (WinAnimationCropRect.x == 192 && WinAnimationCropRect.y == 0)
		{
			HandleSDLEvents();
		}
	}
	else
	{
		WinTimer.Update(10);
	}
}