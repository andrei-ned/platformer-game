#include "Tilemap.h"
#include "Sprite.h"
#include "Collider.h"

using namespace DirectX::SimpleMath;


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

std::vector<GameObject*> Tilemap::addTiles(std::vector<std::pair<int, int>> positions)
{
	std::vector<GameObject*> newTiles;
	for (unsigned int i = 0; i < positions.size(); i++)
	{
		if (exists(positions.at(i)))
			continue;
		newTiles.push_back(addTile(positions.at(i)));
	}
	return newTiles;
}

std::vector<GameObject*> Tilemap::fillTiles(std::pair<int, int> pos1, std::pair<int, int> pos2)
{
	std::vector<GameObject*> newTiles;
	int minX = min(pos1.first, pos2.first);
	int maxX = max(pos1.first, pos2.first);
	int minY = min(pos1.second, pos2.second);
	int maxY = max(pos1.second, pos2.second);

	for (int x = minX; x <= maxX; x++)
	{
		for (int y = minY; y <= maxY; y++)
		{
			if (exists(x, y))
				continue;
			GameObject* go = new GameObject;
			go->mPos = Vector2(x*mTileSize.x, y*mTileSize.y);
			auto spr = go->addComponent<Sprite>();
			spr->setTexture(*mTile.getTexture(0));
			spr->mScale = mTile.mScale + Vector2(0.005f, 0.005f);
			mTileGameObjects.insert({ {x,y},go });
			newTiles.push_back(go);
		}
	}
	auto col = mTileGameObjects[{minX, minY}]->addComponent<Collider>();
	col->mSize = Vector2(static_cast<float>(maxX - minX + 1), static_cast<float>(maxY - minY + 1)) * mTileSize;
	return newTiles;
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
	}
}

bool Tilemap::exists(int x, int y) const
{
	return exists({ x,y });
}

bool Tilemap::exists(std::pair<int, int> pos) const
{
	return mTileGameObjects.find(pos) != mTileGameObjects.end();
}
