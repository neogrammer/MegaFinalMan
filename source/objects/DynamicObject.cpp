#include "DynamicObject.h"

DynamicObject::DynamicObject(Cfg::Textures tex_, sf::Vector2f size_, sf::Vector2f pos_)
	: GameObject{}
	, animator{this}
	, currTex{tex_}
	, rigidBody{dynamic_cast<DynamicObject*>(this)}
{
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
	pass->setPosition({ rigidBody.getPosition().x - rigidBody.getTexOffset(animator.getCurrID(), animator.getCurrDir(), animator.getCurrIndex()).x,rigidBody.getPosition().y - rigidBody.getTexOffset(animator.getCurrID(), animator.getCurrDir(), animator.getCurrIndex()).y });
	return std::move(pass);
}

BoundingBox DynamicObject::getBBox()
{
	return rigidBody.getBBox();
}

void DynamicObject::setPosition(sf::Vector2f pos_)
{
	rigidBody.setPosition(pos_);

}

sf::Vector2f DynamicObject::getPosition()
{
	return rigidBody.getPosition();
}

float& DynamicObject::BBoxWidth()
{
	return rigidBody.BBoxWidth(animator.getCurrID(), animator.getCurrDir(), animator.getCurrIndex());
}

float& DynamicObject::BBoxHeight()
{
	return rigidBody.BBoxHeight(animator.getCurrID(), animator.getCurrDir(), animator.getCurrIndex());

}

float& DynamicObject::TexOffX()
{
	return rigidBody.TexOffX(animator.getCurrID(), animator.getCurrDir(), animator.getCurrIndex());

}

float& DynamicObject::TexOffY()
{
	return rigidBody.TexOffY(animator.getCurrID(), animator.getCurrDir(), animator.getCurrIndex());

}

sf::Vector2f DynamicObject::getFrameSize()
{
	return animator.getFrameSize();
}

sf::Vector2f DynamicObject::getBBoxSize()
{
	return rigidBody.getSize(animator.getCurrID(), animator.getCurrDir(), animator.getCurrIndex());
}

sf::Vector2f DynamicObject::getTexOffset()
{
	return rigidBody.getTexOffset(animator.getCurrID(), animator.getCurrDir(), animator.getCurrIndex());
}

std::string DynamicObject::getCurrAnimID()
{
	return animator.getCurrID();
}

void DynamicObject::queueAnim(std::string id_)
{
	animator.animSet.setTransBuffer(id_);
}

void DynamicObject::updateAnimState()
{
	if (animator.animSet.isTransitioning())
	{
		animator.animSet.frameIdx = 0U;
	}
	animator.animSet.updateCurrentAnim();
}

sf::Vector2f DynamicObject::getVelocity()
{
	return this->rigidBody.getVelocity();
}

void DynamicObject::setVelocity(sf::Vector2f vel_)
{
	this->rigidBody.setVelocity(vel_);
}

void DynamicObject::update(float gameTime_)
{
}
