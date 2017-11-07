#pragma once
#include "Entities.h"

class Trap :
	public Entities
{
public:
	Trap();
	~Trap();

	void Update(PlayState* _state) override;

	bool CollideWith(Entities * _other);

protected:
	int spriteIndex = 1;
	bool active;
};