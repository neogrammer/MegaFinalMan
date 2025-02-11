#ifndef RIGID_BODY_H__
#define RIGID_BODY_H__
#include <SFML/System/Vector2.hpp>
#include "BoundingBox.h"
#include <string>
#include <unordered_map>
#include <vector>
class GameObject;
class RigidBody
{
	friend class AnimSet;
	GameObject* owner;
	float posx{}, posy{};
	float velx{}, vely{};
	std::unordered_map<std::string, std::unordered_map<std::string, std::vector<BoundingBox>> > aabb;
public:
	RigidBody() = delete;
	RigidBody(GameObject* dyno_, sf::Vector2f pos_={ 0.f,0.f }, sf::Vector2f vel_ = { 0.f,0.f });
	~RigidBody();

	BoundingBox getBBox();
	float& BBoxWidth(std::string id_, std::string dir_, int index_);
	float& BBoxHeight(std::string id_, std::string dir_, int index_);
	float& TexOffX(std::string id_, std::string dir_, int index_);
	float& TexOffY(std::string id_, std::string dir_, int index_);
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos_);
	void move(sf::Vector2f dx_, float gameTime_);

	sf::Vector2f getSize(std::string animName_, std::string dir_, int frameIdx_);
	void setSize(sf::Vector2f size_, std::string animName_, std::string dir_, int frameIdx_);

	sf::Vector2f getVelocity();
	void setVelocity(sf::Vector2f vel_);
	void accelerate(sf::Vector2f acc_, float gameTime_);

	inline float& getX() { return posx; }
	inline float& getY() { return posy; }
	inline float& getVelX() { return velx; }
	inline float& getVelY() { return vely; }

	sf::Vector2f getTexOffset(std::string animName_, std::string dir_, int frameIdx_);
	void setTexOffset(sf::Vector2f offset_, std::string animName_, std::string dir_, int frameIdx_);

	void setRigidBody();
};

#endif