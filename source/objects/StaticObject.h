#ifndef STATIC_OBJECT_H__
#define STATIC_OBJECT_H__
#include "GameObject.h"
#include "../animation/Animator.h"
#include "../resources/Cfg.h"

#include "../physics/BoundingBox.h"
class StaticObject : public GameObject
{
protected:
	sf::Vector2i texPosition;
	float posx, posy;
	Cfg::Textures currTex;
	BoundingBox bbox;
	bool empty;
public:
	StaticObject(Cfg::Textures tex_ = Cfg::Textures::Invariant, sf::Vector2f size_ = sf::Vector2f{ 50.f,50.f }, sf::Vector2f pos_ = sf::Vector2f{ 0.f,0.f }, sf::Vector2i texPos_ = { 0,0 }, sf::Vector2f frameSize_ = { 50.f,50.f });
	virtual ~StaticObject() override;
	bool isEmpty();
	void setEmpty(bool cond_);

	inline Cfg::Textures getTexType() { return this->currTex; }
	BoundingBox& getBBox();
	sf::Texture& getTex() const;
	std::unique_ptr<sf::Sprite> sprite();
	void setPosition(sf::Vector2f pos_);
	sf::Vector2f getPosition();
	void setSize(sf::Vector2f size_);
	sf::Vector2f getSize();
	sf::IntRect getTexRect();
};
#endif