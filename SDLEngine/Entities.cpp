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