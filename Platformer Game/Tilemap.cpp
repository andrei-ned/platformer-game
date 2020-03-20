#include "Tilemap.h"
#include "Sprite.h"
#include "Collider.h"


Tilemap::Tilemap(Tile tile) : mTile(tile)
{
}

Tilemap::Tilemap(Tile tile, Vector2 tileSize) : mTile(tile), mTileSize(tileSize)
{
}

Tilemap::~Tilemap()
{
}

GameObject* Tilemap::addTile(int x, int y)
{
	return addTile(std::make_pair(x, y));
}

GameObject* Tilemap::addTile(std::pair<int, int> pos)
{
	GameObject* go = new GameObject;
	go->mPos = Vector2(pos.first*mTileSize.x, pos.second*mTileSize.y);
	auto spr = go->addComponent<Sprite>();
	spr->setTexture(*mTile.getTexture(0));
	spr->mScale = mTile.mScale;
	go->addComponent<Collider>();
	mTileGameObjects.insert({ pos,go });
	return go;
}

std::vector<GameObject*> Tilemap::addTiles(Tile& tile, std::vector<std::pair<int, int>> positions)
{
	std::vector<GameObject*> mNewTiles;
	for (unsigned int i = 0; i < positions.size(); i++)
	{
		mNewTiles.push_back(addTile(positions.at(i)));
	}
	return mNewTiles;
}

void Tilemap::updateTilemap()
{
	for (auto& pair : mTileGameObjects)
	{
		int mask = 0;
		int x = pair.first.first;
		int y = pair.first.second;
		if (mTileGameObjects.find({ x-1,y }) != mTileGameObjects.end())
			mask |= Tile::Adjacency::Left;
		if (mTileGameObjects.find({ x+1,y }) != mTileGameObjects.end())
			mask |= Tile::Adjacency::Right;
		if (mTileGameObjects.find({ x,y-1 }) != mTileGameObjects.end())
			mask |= Tile::Adjacency::Top;
		if (mTileGameObjects.find({ x,y+1 }) != mTileGameObjects.end())
			mask |= Tile::Adjacency::Bottom;
		pair.second->getComponent<Sprite>()->setTexture(*mTile.getTexture(mask));
		if (mTile.getColliderBounds(mask).has_value())
		{
			pair.second->getComponent<Collider>()->setBounds(mTile.getColliderBounds(mask).value());
		}
	}
}
