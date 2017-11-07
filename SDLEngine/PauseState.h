#pragma once
#include "GameState.h"
#include "Timer.h"

class Timer;
class PauseState : public GameState
{
	Timer strobeTimer;
	bool strobe;
public:
	PauseState(GameData *_gameData);
	~PauseState();

	bool HandleSDLEvents() override;
	void Update(float deltaTime) override;
	void Draw() override;
};

