#pragma once
#include "Entities.h"

class Trap :
	public Entities
{
public:
	Trap();
	~Trap();

protected:
	int spriteIndex = 1;
	bool active;
};