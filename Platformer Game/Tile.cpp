#include "Tile.h"

using namespace DirectX::SimpleMath;


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

ID3D11ShaderResourceView* Tile::getTexture(int mask) const
{
	return mTileDetails.at(mask).texture;
}
