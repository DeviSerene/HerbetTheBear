#include "Coin.h"
#include "PlayState.h"


Coin::Coin()
	: Entities()
{
	fileName = "coin_sheet.png";

	EntityPosition.x = 0;
	EntityPosition.y = 0;
	EntityPosition.w = EntityPosition.h = 16;

	cropRect.x = 0;
	cropRect.y = 0;
	cropRect.w = cropRect.h = 16;
}


Coin::~Coin()
{

}

void Coin::Update(PlayState *_state)
{
	if (animationTimer.Completed())
	{
		cropRect.x += 16;
		if (cropRect.x >= 112)
		{
			cropRect.x = 0;
		}

		animationTimer.Reset();
	}

	animationTimer.Update(_state->delta);
}

void Coin::Draw(SpriteFactory *_sprite)
{
	
}

void Coin::CoinCollected()
{
	// If player collides with coin, gets destoryed
}

void Coin::SetCoinPosRect(int _x, int _y)
{
	EntityPosition.x = _x;
	EntityPosition.y = _y;
}

SDL_Rect Coin::getCoinPosRect()
{
	return EntityPosition;
}

SDL_Rect Coin::getCoinCropRect()
{
	return cropRect;
}