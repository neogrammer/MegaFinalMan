#include "RigidBody.h"

RigidBody::RigidBody()
	: aabb{}
{}

RigidBody::~RigidBody()
{}

sf::Vector2f RigidBody::getPosition()
{
	return sf::Vector2f{aabb.x,aabb.y};
}

void RigidBody::setPosition(sf::Vector2f pos_)
{
	aabb.x = pos_.x;
	aabb.y = pos_.y;

}

sf::Vector2f RigidBody::getSize()
{
	return sf::Vector2f(aabb.w,aabb.h);
}

void RigidBody::setSize(sf::Vector2f size_)
{
	aabb.w = size_.x;
	aabb.h = size_.y;

}
