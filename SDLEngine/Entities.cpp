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
	SDL_Rect otherPos = _other->getPosition();
	if ((EntityPosition.x <= otherPos.x + otherPos.w && EntityPosition.x + EntityPosition.w >= otherPos.x
		&& EntityPosition.y <= otherPos.y + otherPos.h && EntityPosition.y + EntityPosition.h >= otherPos.y))
		return true;
	return false;
}