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
	cropRect.w = cropRect.h = 32;

	DestoryCoin = false;

	hitboxWidth = 16;
	hitboxHeight = 16;
}

Coin::~Coin()
{

}

void Coin::Update(PlayState *_state)
{
	// Goes through crop sheet
	Entities::Update(_state);
	/*if (animationTimer.Completed())
	{
		cropRect.x += 16;
		if (cropRect.x >= 112)
		{
			cropRect.x = 0;
		}

		animationTimer.Reset();
	}

	animationTimer.Update(_state->delta);*/
	

}

void Coin::Draw(SpriteFactory *_sprite)
{
	// Sets the coins position in world space
	worldPos = SDL_Rect{ EntityPosition.x - (int)cameraX, EntityPosition.y - (int)cameraY, EntityPosition.w, EntityPosition.h };
	_sprite->Draw("assets/textures/heart.png", worldPos, cropRect, false);
}


bool Coin::CollideWith(Entities* _other)
{
	if (Entities::CollideWith(_other))
	{
		DestoryCoin = true;
		
	}
	else
	{
		DestoryCoin = false;
	}

	return DestoryCoin;
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

SDL_Rect Coin::getWorldPosRect()
{
	return worldPos;
}

bool Coin::getIfCoinDestroyed()
{
	return DestoryCoin;
}