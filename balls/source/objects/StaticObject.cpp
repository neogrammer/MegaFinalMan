#include "StaticObject.h"

StaticObject::StaticObject(Cfg::Textures tex_, sf::Vector2f size_, sf::Vector2f pos_, sf::Vector2i texPos_, sf::Vector2f frameSize_)
	: GameObject{}
	, texPosition{texPos_}
	, currTex{ tex_ }
	, rigidBody{}
	, frameSize{frameSize_}
{
	rigidBody.setSize(size_);
	rigidBody.setPosition(pos_);
	// set framesize in derived
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
	pass->setTextureRect(sf::IntRect(sf::Vector2i(texPosition),sf::Vector2i(frameSize)));
		//sf::IntRect(texPosition.x, texPosition.y, (int)frameSize.x, (int)frameSize.y));
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

sf::Vector2f StaticObject::getSize()
{
	return rigidBody.getSize();
}

sf::IntRect StaticObject::getTexRect()
{
	return sf::IntRect(sf::Vector2i(texPosition), sf::Vector2i(frameSize));
}
