#ifndef RIGID_BODY_H__
#define RIGID_BODY_H__
#include <SFML/System/Vector2.hpp>

namespace phys
{
	struct BoundingBox
	{
		float x, y, w, h;
	};
}

using namespace phys;

class RigidBody
{
	BoundingBox aabb;

public:
	RigidBody();
	~RigidBody();

	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos_);

	sf::Vector2f getSize();
	void setSize(sf::Vector2f size_);
};

#endif