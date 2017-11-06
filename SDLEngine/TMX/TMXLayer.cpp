#include "TMXLayer.h"

#include <stdlib.h>
#include <string.h>

TMXLayer::TMXLayer(int width, int height, const char *name, const char *tileData)
	:width(width), height(height), name(name)
{
	int len = strlen(tileData), count = 0;
	char buf[4];
	short buf_it = 0;
	tiles = (int*)malloc(width * height * sizeof(int));

	for (int i = 0; i < len; i++) {
		char ch = tileData[i];
		if (ch == ',') {
			tiles[count] = strtol(buf, 0, 10);
			count++;
			for (int j = 0; j < 4; j++)
				buf[j] = 0;
			buf_it = 0;
			continue;
		}
		if (buf_it > 3 || ch == ' ' || ch == '\n')
			continue;
		buf[buf_it] = ch;
		buf_it++;
	}
	tiles[count] = strtol(buf, 0, 10);
}


TMXLayer::~TMXLayer()
{
}
