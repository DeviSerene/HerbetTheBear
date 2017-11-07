#include "Entities.h"
#include "PlayState.h"


Entities::Entities()
{
	drawnPlayer = false;
}

void Entities::Update(PlayState* _state) {
	cameraX = _state->cameraX;
	cameraY = _state->cameraY;
}
 
bool Entities::CollideWith(Entities *_other) {
	SDL_Rect hitbox = GetHitbox();
	SDL_Rect otherPos = _other->GetHitbox();
	if ((hitbox.x <= otherPos.x + otherPos.w && hitbox.x + hitbox.w >= otherPos.x
		&& hitbox.y <= otherPos.y + otherPos.h && hitbox.y + hitbox.h >= otherPos.y))
		return true;
	return false;
}