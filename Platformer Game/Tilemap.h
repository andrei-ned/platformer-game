#pragma once
#include "GameObject.h"
#include "Tile.h"
#include <map>


// Tool to generate gamme objects on a grid
class Tilemap
{
public:
	Vector2 mTileSize;

	Tilemap(Tile tile);
	Tilemap(Tile tile, Vector2 tileSize);
	~Tilemap();
	
	// Make game object out of tile and put into map
	GameObject* addTile(int x, int y);
	GameObject* addTile(std::pair<int, int> pos);
    std::vector<GameObject*> addTiles(Tile& tile, std::vector<std::pair<int, int>> positions);
	// Update tile visuals based on adjacent tiles
	void updateTilemap();
private:
	std::map<std::pair<int, int>, GameObject*> mTileGameObjects;
	Tile mTile;
};

