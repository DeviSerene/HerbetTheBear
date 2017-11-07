#include "Teddy.h"
#include "Player.h"
#include "PlayState.h"

Teddy::Teddy(SDL_Rect _pos)
{
	EntityPosition = _pos;
}


Teddy::~Teddy()
{
}

bool Teddy::CollideWith(Entities *_other) {
	if (Entities::CollideWith(_other)) {
		Player *p = dynamic_cast<Player*> (_other);
		if (p != NULL) {
			//Level complete, change
		}
 		return true;
	}
	return false;
}

void Teddy::Draw(SpriteFactory *_factory) {
	EntityPosition.x -= (int)cameraX;
	EntityPosition.y -= (int)cameraY;
	_factory->Draw("assets/textures/herbert_teddy.png", EntityPosition);
	EntityPosition.x += (int)cameraX;
	EntityPosition.y += (int)cameraY;
}

void Teddy::Update(PlayState *_state) {
	Entities::Update(_state);
	CollideWith(_state->player);
}
