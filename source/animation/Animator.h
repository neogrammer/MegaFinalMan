#ifndef ANIMATOR_H__
#define ANIMATOR_H__
#include "AnimSet.h"
class RigidBody;
class DynamicObject;
class Animator
{
	friend class DynamicObject;
	AnimSet animSet;
public:
	DynamicObject* owner;
public:
	Animator(DynamicObject* owner_);
	~Animator();
	sf::IntRect getFrame();
	int getCurrIndex();
	sf::Vector2f getFrameSize();
	void addAnim(std::string id_, int numFrames_ = 1, sf::Vector2f frameSize_ = sf::Vector2f{ 50.f,50.f }, float frameDelay_ = { 0.13f }, sf::Vector2f startPixel_ = sf::Vector2f{ 0.f,0.f }, std::string dirType_ = "Uni", bool genOtherDirection_ = false, bool loops_ = true, bool loopWaits_ = false, float loopDelay_ = 0.f, sf::Vector2f texOffset_ = { 0.f,0.f }, sf::Vector2f bboxSize_ = { 0.f,0.f });
	AnimSet& getAnims();
	std::string getCurrID();
	std::string getCurrDir();

	void setCurrIndex(int idx_);


	

	void update(float gameTime_);
	void setDir(std::string dir_);

};

#endif