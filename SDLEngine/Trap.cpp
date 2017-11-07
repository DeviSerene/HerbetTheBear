#include "Trap.h"
#include <iostream>
#include "PlayState.h"

Trap::Trap()
{

}
Trap::~Trap()
{

}

void Trap::Update(PlayState* _state)
{
	Entities::Update(_state);
	CollideWith(_state->player);
}

bool Trap::CollideWith(Entities* _other)
{
	if (Entities::CollideWith(_other)) {
		//std::cout << "Collision!!";
		//Kill player or somit
	}
	return false;
}
