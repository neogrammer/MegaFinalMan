#ifndef DYNAMIC_OBJECT_H__
#define DYNAMIC_OBJECT_H__
#include "GameObject.h"
#include "../animation/Animator.h"
#include "../resources/Cfg.h"
#include "../physics/RigidBody.h"

class DynamicObject : public GameObject
{
	friend class RigidBody;
protected:
	Animator animator;
	Cfg::Textures currTex;
	RigidBody rigidBody;
	
public:
	DynamicObject(Cfg::Textures tex_ = Cfg::Textures::Invariant, sf::Vector2f size_ = sf::Vector2f{ 50.f,50.f }, sf::Vector2f pos_ = sf::Vector2f{ 0.f,0.f });
	virtual ~DynamicObject() override;

	sf::Texture& getTex() const;
	std::unique_ptr<sf::Sprite> sprite();
	BoundingBox getBBox();
	void setPosition(sf::Vector2f pos_);
	sf::Vector2f getPosition();
	float& BBoxWidth();
	float& BBoxHeight();
	float& TexOffX();
	float& TexOffY();
	sf::Vector2f getFrameSize();
	sf::Vector2f getBBoxSize();
	sf::Vector2f getTexOffset();

	inline RigidBody& getRigid() {
		return rigidBody;
	}

	std::string getCurrAnimID();
	void queueAnim(std::string id_);
	void updateAnimState();
	sf::Vector2f getVelocity();
	void setVelocity(sf::Vector2f vel_);

	virtual void update(float gameTime_) override;

};
#endif