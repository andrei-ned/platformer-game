#pragma once
#include "GameObject.h"
#include <optional>
#include "Helpers.h"

// Contains information about setting up a game object on a tilemap
class Tile
{
public:
	enum Adjacency {
		Left   = 1 << 0,
		Top    = 1 << 1,
		Right  = 1 << 2,
		Bottom = 1 << 3
	};

	Vector2 mScale;

	Tile();
	~Tile();

	void setTexture(int adjacencyMask, ID3D11ShaderResourceView& texture);
	//void setColliderBounds(int adjacencyMask, RECTF bounds);
	ID3D11ShaderResourceView* getTexture(int mask) const;
	//std::optional<RECTF> getColliderBounds(int mask) const;
private:
	struct TileDetails
	{
		ID3D11ShaderResourceView* texture;
		//std::optional<RECTF> colliderBounds;
	};

	std::vector<TileDetails> mTileDetails;
};

