#include "DynamicObject.h"

DynamicObject::DynamicObject(Cfg::Textures tex_, sf::Vector2f size_, sf::Vector2f pos_)
	: GameObject{}
	, animator{}
	, currTex{tex_}
	, rigidBody{}
{
	rigidBody.setSize(size_);
	rigidBody.setPosition(pos_);


}

DynamicObject::~DynamicObject()
{
}

sf::Texture& DynamicObject::getTex() const
{
	return Cfg::textures.get((int)currTex);
}

std::unique_ptr<sf::Sprite> DynamicObject::sprite()
{
	std::unique_ptr<sf::Sprite> pass;
	pass = std::make_unique<sf::Sprite>();
	pass->setTexture(getTex());
	pass->setTextureRect(animator.getFrame());
	pass->setPosition(rigidBody.getPosition());

	return std::move(pass);
}

void DynamicObject::setPosition(sf::Vector2f pos_)
{
	rigidBody.setPosition(pos_);

}

sf::Vector2f DynamicObject::getPosition()
{
	return rigidBody.getPosition();
}
