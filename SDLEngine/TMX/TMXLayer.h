#pragma once

#include <string>
#include <map>
struct TMXLayer
{
	int width, height;
	const char *name;
	int a;
	int *tiles;
	std::map<std::string, std::string> stringProperties;
	std::map<std::string, int> intProperties;
	std::map<std::string, float> floatProperties;
	std::map<std::string, bool> boolProperties;

	TMXLayer(int width, int height, const char* name, const char *tileData);
	~TMXLayer();
};

