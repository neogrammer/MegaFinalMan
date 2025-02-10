#include <world/Tile.h>

std::unique_ptr<sf::Sprite> Tile::spr()
{
	std::unique_ptr<sf::Sprite> tmp = std::make_unique<sf::Sprite>();
	tmp->setTexture(*frame.texture);
	tmp->setTextureRect(frame.texRect);
	tmp->setPosition({ pos.x, pos.y });
	return std::move(tmp);
}
