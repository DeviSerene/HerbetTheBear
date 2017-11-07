#pragma once
#include "Entities.h"
class Teddy : public Entities
{
public:
	Teddy(SDL_Rect _pos);
	~Teddy();

	bool CollideWith(Entities *_other) override;
	void Draw(SpriteFactory *_factory) override;
	void Update(PlayState *_state) override;
};

