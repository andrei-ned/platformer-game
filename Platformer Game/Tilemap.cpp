#include "Tilemap.h"
#include "Sprite.h"
#include "Collider.h"


Tilemap::Tilemap()
{
}

Tilemap::Tilemap(Vector2 tileSize) : mTileSize(tileSize)
{
}

Tilemap::~Tilemap()
{
}

GameObject* Tilemap::addTile(Tile& tile, int x, int y)
{
	return addTile(tile, std::make_pair(x, y));
}

GameObject* Tilemap::addTile(Tile& tile, std::pair<int, int> pos)
{
	GameObject* go = new GameObject;
	go->mPos = Vector2(pos.first*mTileSize.x, pos.second*mTileSize.y);
	auto spr = go->addComponent<Sprite>();
	spr->setTexture(*tile.getTexture(0));
	spr->mScale = tile.mScale;
	go->addComponent<Collider>();
	mTiles.insert({ pos,go });
	return go;
}

std::vector<GameObject*> Tilemap::addTiles(Tile& tile, std::vector<std::pair<int, int>> positions)
{
	std::vector<GameObject*> mNewTiles;
	for (unsigned int i = 0; i < positions.size(); i++)
	{
		mNewTiles.push_back(addTile(tile, positions.at(i)));
	}
	return mNewTiles;
}

void Tilemap::updateTilemap()
{
	for (auto& pair : mTiles)
	{

	}
}
