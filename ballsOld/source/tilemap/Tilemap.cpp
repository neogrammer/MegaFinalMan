#include "Tilemap.h"
#include "Tile.h"
Tilemap::Tilemap()
	: tileset{}
{
}

Tilemap::~Tilemap()
{
}

std::vector<Tile*> Tilemap::getVisibleTiles()
{
	return std::vector<Tile*>();
}

std::vector<Tile*> Tilemap::getTilesInArea(int top_, int left_, int width_, int height_)
{
	return std::vector<Tile*>();
}

void Tilemap::setTileset(Cfg::Textures tex_, int numTiles_, int pitch_, sf::Vector2f size_)
{
	tileset.reset();
	tileset = std::make_unique<Tileset>(tex_, numTiles_, pitch_, size_);
}

void Tilemap::render(sf::RenderWindow& wnd_)
{
	for (auto& i : tileset->getTiles())
	{
		wnd_.draw(*i->sprite());
	}
}
