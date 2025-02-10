#include "Tileset.h"
#include "Tile.h"
Tileset::Tileset(Cfg::Textures tex_, int numTiles_, int pitch_, sf::Vector2f size_)
	: tileVec{}
	, numTiles{ numTiles_ }
	, cols{pitch_}
	, rows{}
	, tex{tex_}
	, tileSize{size_}
{
	tileVec.clear();
	tileVec.reserve(numTiles_);
	
	rows = (numTiles_ / pitch_) + 1;

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < pitch_; x++)
		{
			if ((y * pitch_ + x) >= numTiles_)
			{
				break;
			}
			else
			{
				tileVec.emplace_back(std::make_unique<Tile>(tex_, size_, sf::Vector2f( (float)x * size_.x, (float)y * size_.y ), sf::Vector2i(x * (int)size_.x, y * (int)size_.y)));
			}
		}
	}
}

Tileset::~Tileset()
{
}


std::vector<std::unique_ptr<Tile>>& Tileset::getTiles()
{
	return tileVec;
}

Cfg::Textures Tileset::getTexType()
{
	return tex;
}

sf::IntRect Tileset::getTileTexRect(int index)
{
	return sf::IntRect(sf::Vector2i(tileVec.at(index)->getTexPosition()), sf::Vector2i(tileVec.at(index)->getSize()));
}
