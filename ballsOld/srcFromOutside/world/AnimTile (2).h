#pragma once
#include <world/Tile.h>
#include <unordered_map>
#include <string>
#include <misc/Animation.h>
#include <vector>
#include <misc/BBox.h>

class AnimTile : public Tile
{
	std::unordered_map<std::string, Animation> anims{};
	std::unordered_map<std::string, std::vector<BBox>> bboxes{};
	std::string currAnim{ "default" };

public:
	using Tile::Tile;

	void loadAnimation(std::string name_, sf::Texture& tex_, int numFrames_, std::vector<v2> offsets_, std::vector<v2> bboxes_, v2 frameSize_, v2 startPixel);
};