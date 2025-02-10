#pragma once

#include <world/Tile.h>
#include <world/AnimTile.h>
#include <vector>
#include <misc/v2.h>
class Tileset
{
	
public:

	Tileset(v2 size_, int id_);
	Tileset() = delete;
	~Tileset() = default;
	Tileset(const Tileset&) = delete;
	Tileset(Tileset&&) = delete;
	Tileset& operator=(const Tileset&) = delete;
	Tileset& operator=(Tileset&&) = delete;

	int _id{};
	v2 _size{};
	std::vector<Tile> _tiles{};
	std::vector<AnimTile> _animTiles{};
	std::string name{};
	void addTile(const Tile& aTile);
	void load(v2 tileSize, int numTiles, sf::Texture& tex_, std::string solidFile);
	void loadAnimTile(std::string name_, v2 startPos, v2 tileSize, int numFrames, sf::Texture& tex_);
};