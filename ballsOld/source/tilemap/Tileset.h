#ifndef TILESET_H__
#define TILESET_H__
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "../resources/Cfg.h"
class Tile;
class Tileset
{

	std::vector<std::unique_ptr<Tile> > tileVec;
	Cfg::Textures tex;
	
	int numTiles{};
	int cols{};
	int rows{};

	sf::Vector2f tileSize{};

public:
	Tileset(Cfg::Textures tex_, int numTiles_, int pitch, sf::Vector2f size_);
	~Tileset();

	std::vector < std::unique_ptr<Tile> >& getTiles();
};


#endif