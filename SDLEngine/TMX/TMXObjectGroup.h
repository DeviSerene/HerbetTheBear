#pragma once
#include <vector>

#include "TMXObject.h"
struct TMXObjectGroup
{
	std::string name;
	std::vector<TMXObject*> objects;

	TMXObjectGroup(const char *name);
	~TMXObjectGroup();
};

