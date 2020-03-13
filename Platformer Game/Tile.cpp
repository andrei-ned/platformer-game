#include "Tile.h"



Tile::Tile() : mTextures(16), mScale(Vector2(1,1))
{
}


Tile::~Tile()
{
}

void Tile::setTexture(int adjacencyMask, ID3D11ShaderResourceView& texture)
{
	mTextures.at(adjacencyMask) = &texture;
}

ID3D11ShaderResourceView* Tile::getTexture(int mask) const
{
	return mTextures.at(mask);
}
