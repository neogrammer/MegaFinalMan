#include "StaticObject.h"

StaticObject::StaticObject(Cfg::Textures tex_, sf::Vector2f size_, sf::Vector2f pos_, sf::Vector2i texPos_, sf::Vector2f frameSize_)
	: GameObject{}
	, texPosition{texPos_}
	, currTex{ tex_ }
	, bbox{ size_.x, size_.y, 0.f, 0.f }
	, posx{pos_.x}, posy{pos_.y}
{
}

StaticObject::~StaticObject()
{
}

bool StaticObject::isEmpty()
{
	return empty;
}

void StaticObject::setEmpty(bool cond_)
{
	empty = cond_;
}


BoundingBox& StaticObject::getBBox()
{
	return bbox;
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
	pass->setTextureRect(sf::IntRect(sf::Vector2i(texPosition), sf::Vector2i({(int)bbox.w,(int)bbox.h})));
	pass->setPosition({posx,posy});
	return std::move(pass);
}

void StaticObject::setPosition(sf::Vector2f pos_)
{
	posx=pos_.x;
	posy = pos_.y;
}

sf::Vector2f StaticObject::getPosition()
{
	return { posx,posy };
}

void StaticObject::setSize(sf::Vector2f size_)
{
	bbox.w = size_.x;
	bbox.h = size_.y;
}

sf::Vector2f StaticObject::getSize()
{
	return { bbox.w,bbox.h};
}

sf::IntRect StaticObject::getTexRect()
{
	return sf::IntRect(sf::Vector2i(texPosition), sf::Vector2i((int)bbox.w, (int)bbox.h));
}
