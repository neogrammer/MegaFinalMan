#include "Tilemap.h"
#include "Tile.h"
Tilemap::Tilemap()
	: tileset{}
	, tiles{}
	, pitch{}
{
	tiles.clear();

	
}

Tilemap::~Tilemap()
{
}

std::vector<Tile*> Tilemap::getVisibleTiles()
{
	std::vector<Tile*> tmp;
	tmp.clear();
	tmp.reserve(this->tiles.size());
	for (int i = 0; i < this->tiles.size(); i++)
	{
		if (!(tiles[i]->empty))
			tmp.push_back(tiles[i].get());
	}
	tmp.shrink_to_fit();
	return tmp;
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

void Tilemap::setMap(int* tileData, int numTiles_, int pitch_)
{
	pitch = pitch_;
	tiles.clear();
	tiles.reserve(numTiles_);

	int rows = numTiles_ / pitch_;

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < pitch_; x++)
		{
			int num = tileData[y * pitch_ + x];  // this will return the number corresponding to the tileset tiles index at the location in the map onscreen
	
			if (num == -1)
			{
				tiles.emplace_back(std::make_unique<Tile>(Cfg::Textures::EmptyTile, sf::Vector2f{ 50.f,50.f }, sf::Vector2f{ 0.f,0.f }));
				tiles.back()->setPosition(sf::Vector2f{ (float)(x * 50.f), (float)(y * 50.f) });
				tiles.back()->setEmpty(true);
			}
			else
			{
				auto& tRef = tileset->getTiles().at(num);

				sf::Vector2f tmpTexPos = (sf::Vector2f)tileset->getTiles().at(num)->getTexPosition();

				tiles.emplace_back(std::make_unique<Tile>(tileset->getTexType(), tRef->getSize(), sf::Vector2f{ (float)(x)*tileset->getTiles().at(num)->bbox.w, (float)(y)*tileset->getTiles().at(num)->bbox.h }, tileset->getTiles().at(num)->getTexPosition()));
				tiles.back()->setEmpty(false);

			}
		}
	}
}

int Tilemap::getPitch()
{
	return pitch;
}

int Tilemap::getNumTiles()
{
	return (int)tiles.size();
}

sf::Vector2f Tilemap::getTileSize()
{
	return tileset->getTiles().at(0)->getSize();
}

Cfg::Textures Tilemap::getCurrTexType()
{
	return tileset->getTexType();
}

void Tilemap::render(sf::RenderWindow& wnd_)
{
	//for (auto& i : tileset->getTiles())
	for (auto& i : tiles)
	{
		
		wnd_.draw(*i->sprite());
	}
}
