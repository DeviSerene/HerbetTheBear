#pragma once
#include "Entities.h"
#include "Timer.h"


class Coin : public Entities
{
protected:

	SDL_Rect cropRect;
	Timer animationTimer;

	SDL_Rect worldPos;

	bool DestoryCoin;

public:
	Coin();
	~Coin();

	void Update(PlayState* _state) override;
	void Draw(SpriteFactory *_sprite) override;
	bool CollideWith(Entities *_other) override;

	void CoinCollected();
	void SetCoinPosRect(int _x, int _y);
	
	SDL_Rect getCoinPosRect();
	SDL_Rect getCoinCropRect();
	SDL_Rect getWorldPosRect();

	bool getIfCoinDestroyed();

};

