#include "StaticObject.h"

StaticObject::StaticObject(Cfg::Textures tex_, sf::Vector2f size_, sf::Vector2f pos_, sf::Vector2i texPos_)
	: GameObject{}
	, texPosition{}
	, currTex{ tex_ }
	, rigidBody{}
{
	rigidBody.setSize(size_);
	rigidBody.setPosition(pos_);
}

StaticObject::~StaticObject()
{
}

sf::Texture& StaticObject::getTex() const
{
	return Cfg::textures.get((int)currTex);
}

std::unique_ptr<sf::Sprite> StaticObject::sprite()
{
	std::unique_ptr<sf::Sprite> pass;
	pass = std::make_unique<sf::Sprite>();
	pass->setTexture(getTex());
	pass->setTextureRect(sf::IntRect(texPosition.x, texPosition.y, rigidBody.getSize().x, rigidBody.getSize().y));
	pass->setPosition(rigidBody.getPosition());

	return std::move(pass);
}

void StaticObject::setPosition(sf::Vector2f pos_)
{
	rigidBody.setPosition(pos_);

}

sf::Vector2f StaticObject::getPosition()
{
	return rigidBody.getPosition();
}
