#pragma once
#include <vector>

#include "tinyxml2.h"

#include "TMXLayer.h"
#include "TMXTileSet.h"
#include "TMXObjectGroup.h"

struct TMXMap
{
	int width, height, tileWidth, tileHeight;
	std::vector<TMXTileSet*> tileSets;
	std::vector<TMXLayer*> layers;
	std::vector<TMXObjectGroup*> objectGroups;

	TMXMap(const char *workingDir, const char *fileName);
	~TMXMap();
};

