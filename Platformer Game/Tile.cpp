#include "Tile.h"



Tile::Tile() : mTileDetails(16), mScale(Vector2(1,1))
{
}


Tile::~Tile()
{
}

void Tile::setTexture(int adjacencyMask, ID3D11ShaderResourceView& texture)
{
	mTileDetails.at(adjacencyMask).texture = &texture;
}

void Tile::setColliderBounds(int adjacencyMask, RECTF bounds)
{
	mTileDetails.at(adjacencyMask).colliderBounds = bounds;
}

ID3D11ShaderResourceView* Tile::getTexture(int mask) const
{
	return mTileDetails.at(mask).texture;
}

std::optional<RECTF> Tile::getColliderBounds(int mask) const
{
	return mTileDetails.at(mask).colliderBounds;
}
