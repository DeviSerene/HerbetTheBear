#pragma once

#include <map>
#include <string.h>

static const enum TMX_OBJECT_SHAPES {TMX_RECTANGLE, TMX_ELLIPSE};
struct TMXObject
{
	int x, y, width, height, id;
	TMX_OBJECT_SHAPES shape;
	std::string type;
	std::map<const char*, std::string> stringProperties;
	std::map<const char*, int> intProperties;
	std::map<const char*, float> floatProperties;
	std::map<const char*, bool> boolProperties;


	TMXObject(int x, int y, int width, int height, int id, std::string type, TMX_OBJECT_SHAPES shape);
	~TMXObject();
};

