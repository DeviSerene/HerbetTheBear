#include "TileMap.h"
#include "TMX\TMXMap.h"
#include <SDL_rect.h>


TileMap::TileMap(int _tileWidth, int _tileHeight, int _width, int _height, std::string _atlas, const char *_workingDir, const char *_level)
	:tileWidth(_tileWidth), tileHeight(_tileHeight), width(_width), height(_height), sprite(_atlas)
{
	TMXMap map = TMXMap(_workingDir, _level);

	tileWidth = map.tileWidth;
	tileHeight = map.tileHeight;
	set = map.tileSets[0];

	for (TMXLayer* layer : map.layers) {
		width = layer->width;
		height = layer->height;
		tileIndices.resize(width * height);

		std::fill(tileIndices.begin(), tileIndices.end(), -1);

		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				tileIndices[(y * width) + x] = layer->tiles[(y * width) + x];
			}
		}
	}
}


TileMap::~TileMap()
{
}

void TileMap::Draw(SpriteFactory *_factory, float _cameraX, float _cameraY, int tileCountX) {

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			int indice = tileIndices[(y * width) + x];

			int tileX = indice % tileCountX;
			int tileY = indice / tileCountX;

			_factory->Draw(sprite, SDL_Rect{ -_cameraX + (x * tileWidth), _cameraY + (y * tileHeight), tileWidth, tileHeight }, SDL_Rect{ tileX * 64, tileY * 64, 64, 64 });
		}
	}
}