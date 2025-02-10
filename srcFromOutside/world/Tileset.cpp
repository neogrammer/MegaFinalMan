#include "Tileset.h"
#include <iostream>
#include <fstream>
Tileset::Tileset(v2 size_, int id_)
{
	_id = id_;
	_size = size_;

}

void Tileset::addTile(const Tile& aTile_)
{
	_tiles.push_back(aTile_);
	_tiles.back().frame.texture = aTile_.frame.texture;

}

void Tileset::load(v2 tileSize_, int numTiles_, sf::Texture& tex_, std::string solidFile)
{
	Tile tmp;
	tmp.bbox = tileSize_;
	tmp.frame = Frame{};
	tmp.frame.texture = &tex_;
	tmp.frame.texOffset = { 0.f,0.f };

	for (int y = 0; y < _size.y; y++)
	{
		for (int x = 0; x < _size.x; x++)
		{
			tmp.pos = v2{x*tileSize_.x,y*tileSize_.y};
			tmp.frame.texRect = sf::IntRect(sf::Vector2i((int)(x * tileSize_.x), (int)(y * tileSize_.y)), sf::Vector2i((int)tileSize_.x, (int)tileSize_.y));
			_tiles.push_back(tmp);
		}
	}

	std::ifstream iFile;
	iFile.open(solidFile);

	if (!iFile.is_open())
	{
		std::cout << "Unable to open file for tileset" << std::endl;
		return;
	}
	else
	{
		for (auto& tile : _tiles)
		{ 
			iFile >> tile.solid;
		}

		iFile.close();
	}
}

void Tileset::loadAnimTile(std::string name_, v2 startPos_, v2 tileSize_, int numFrames_, sf::Texture& tex_)
{
	Tile tmp;
	tmp.bbox = tileSize_;
	tmp.pos = startPos_;
	tmp.frame = Frame{};
	tmp.frame.texture = &tex_;
	tmp.frame.texOffset = { 0.f,0.f };
	name = name_;
	std::vector<v2> offsets;
	std::vector<v2> bboxes;
	for (int i = 0; i < numFrames_; i++)
	{
		//		tmp.frame.texRect = sf::IntRect(sf::Vector2i((int)(startPos_.x + i * tileSize_.x), (int)startPos_.y), sf::Vector2i((int)tileSize_.x, (int)tileSize_.y));
		offsets.push_back(v2{ 0.f,0.f });
		bboxes.push_back(v2{tileSize_.x, tileSize_.y});
	}

	_animTiles.push_back(AnimTile{});
	_animTiles[_animTiles.size() - 1].loadAnimation(name_, tex_, numFrames_, offsets, bboxes, tileSize_, startPos_);


	
}
