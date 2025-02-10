#include "Tile.h"

Tile::Tile(Cfg::Textures tex_, sf::Vector2f size_, sf::Vector2f pos_, sf::Vector2i texPos_)
	: StaticObject{ tex_, size_, pos_, texPos_ , size_}
{
}

Tile::~Tile()
{
}

sf::Vector2i Tile::getTexPosition()
{
	return texPosition;
}
