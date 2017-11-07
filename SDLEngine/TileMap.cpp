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

void TileMap::Collision(SDL_Rect& rect, float velX, float velY) {
	float newVelX = velX, newVelY = velY;

	SDL_Rect newPos = rect;
	newPos.x += velX;
	newPos.y += velY;

	int tileH_X = -1, tileH_Y = -1;
	int tileV_X = -1, tileV_Y = -1;

	int boundLeft = rect.x / tileWidth - 2;
	int boundRight = (rect.x + rect.w) / tileWidth + 2;
	int boundTop = rect.y / tileHeight - 2;
	int boundBottom = (rect.y + rect.h) / tileHeight + 2;

	if (boundLeft < 0)
		boundLeft = 0;
	if (boundRight >= width)
		boundRight = width - 1;
	if (boundTop < 0)
		boundTop = 0;
	if (boundBottom >= height)
		boundBottom = height - 1;

	for (int x = boundLeft; x < boundRight; x++) {
		for (int y = boundTop; y < boundBottom; y++) {
			int tileType = tileIndices[(y * width) + x];

			if (tileType <= 0) continue;

			SDL_Rect tilePos = { x * tileWidth, y * tileHeight, tileWidth, tileHeight };

			if (!(newPos.x <= tilePos.x + tilePos.w && newPos.x + newPos.w >= tilePos.x
				&& newPos.y <= tilePos.y + tilePos.h && newPos.y + newPos.h >= tilePos.y)) continue;

			if (rect.y >= tilePos.y + tilePos.y) {
				tileV_X = x;
				tileV_Y = y;

				if (tileV_X != tileH_X) {
					newVelY = (tilePos.y + tilePos.h) - rect.y;
				}

				if (tileV_Y == tileH_Y) {
					newVelX = velX;
				}
			}
			else if (rect.x >= tilePos.x + tilePos.w) {
				tileH_X = x;
				tileH_Y = y;

				if (tileH_Y != tileV_Y) {
					newVelX = (tilePos.x + tilePos.w) - rect.x;
				}

				if (tileV_X == tileH_X) {
					newVelY = velY;
				}
			}
			else if (rect.x + rect.w <= tilePos.x) {
				tileH_X = x;
				tileH_Y = y;

				if (tileH_Y != tileV_Y) {
					newVelX = tilePos.x - (rect.x + rect.w);
				}

				if (tileV_X == tileH_X) {
					newVelY = velY;
				}
			}
			else if (rect.y + rect.h <= tilePos.y) {
				tileV_X = x;
				tileV_Y = y;
				newVelY = tilePos.y - (rect.y + rect.h);

				//if (tileV_X != tileH_X) {
				//}

				if (tileV_Y == tileH_Y) {
					newVelX = velX;
				}
			}
		}
	}

	rect.x += newVelX;
	rect.y += newVelY;
}


void TileMap::Draw(SpriteFactory *_factory, float _cameraX, float _cameraY, int _tileCountX, int _windowWidth, int _windowHeight) {
	
	int boundLeft = (_cameraX - _windowWidth) / tileWidth - 1;
	int boundRight = (_cameraX + _windowWidth) / tileWidth + 1;
	int boundTop = (_cameraY - _windowHeight) / tileHeight - 1;
	int boundBottom = (_cameraY + _windowHeight) / tileHeight + 1;

	if (boundLeft < 0)
		boundLeft = 0;
	if (boundRight >= width)
		boundRight = width - 1;
	if (boundTop < 0)
		boundTop = 0;
	if (boundBottom >= height)
		boundBottom = height - 1;

	for (int x = boundLeft; x < boundRight; x++) {
		for (int y = boundTop; y < boundBottom; y++) {
			int indice = tileIndices[(y * width) + x];
			if (indice <= 0) continue;
			indice--;

			int tileX = indice % _tileCountX;
			int tileY = indice / _tileCountX;

			_factory->Draw(sprite, SDL_Rect{ (int)(-_cameraX + (x * tileWidth)), (int)(-_cameraY + (y * tileHeight)), tileWidth, tileHeight }, SDL_Rect{ tileX * 64, tileY * 64, 64, 64 });
		}
	}
}