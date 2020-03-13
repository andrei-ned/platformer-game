#pragma once
#include "GameObject.h"
#include "Tile.h"
#include <map>

// 
class Tilemap
{
public:
	Vector2 mTileSize;

	Tilemap();
	Tilemap(Vector2 tileSize);
	~Tilemap();
	
	// Make game object out of tile and put into map
	GameObject* addTile(Tile& tile, int x, int y);
	GameObject* addTile(Tile& tile, std::pair<int, int> pos);
    std::vector<GameObject*> addTiles(Tile& tile, std::vector<std::pair<int, int>> positions);
	// Update tile visuals based on adjacent tiles
	void updateTilemap();
private:
	std::map<std::pair<int, int>, GameObject*> mTiles;
};

