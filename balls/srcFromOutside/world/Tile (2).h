#pragma once
#include <misc/BBox.h>
#include <misc/Frame.h>

// tiles are stationary portions of the map
class Tile
{

public:
	v2 pos{};
	BBox bbox{};
	Frame frame{};
	int solid{};
	Tile() = default;
	~Tile() = default;
	Tile(const Tile& tile_)=default;
	Tile& operator=(const Tile&) = default;
	Tile(Tile&&) = default;
	Tile& operator=(Tile&&) = default;

	std::unique_ptr<sf::Sprite> spr();

};