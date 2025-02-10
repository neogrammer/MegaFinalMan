#pragma once
#include <world/Tileset.h>
#include <string>
class Tilemap
{

public:
	Tilemap() = delete;
	Tilemap(v2 size_, int id_);
	~Tilemap() = default;

	Tilemap(const Tilemap&) = delete;
	Tilemap(Tilemap&&) = delete;
	Tilemap& operator=(const Tilemap&) = delete;
	Tilemap& operator=(Tilemap&&) = delete;

	Tileset tileset;
	int cols{}, rows{};
	std::vector<Tile> _tiles{};
	std::vector<AnimTile> _animTiles{};
	bool  loadMap(const std::string& filename);

	void render(sf::RenderWindow& wnd_, float dt_);
	
};