#ifndef ANIM_SET_H__
#define ANIM_SET_H__
#include <vector>
#include <string>
#include <unordered_map>
#include "Animation.h"
#include <iostream>
#include "../physics/BoundingBox.h"
class Animator;
class RigidBody;
class DynamicObject;
class AnimSet
{
	friend class Animator;
	friend class DynamicObject;
	std::unordered_map<std::string, std::unordered_map<std::string, Animation>>  anims;
//	std::unordered_map<std::string, std::vector<Animation>> animMap; 
	std::unordered_map<std::string, std::vector<std::string>> animTransMap; 
	std::string transBuffer{"None"}; 
	std::string currentAnim{"Default"}; 
	std::string currDir{ "Uni" };
	unsigned int frameIdx{ 0U }; 
	unsigned int currMaxIdx{ 0U };
	bool transitioning{ false };
	bool playing{ true };
	float frameElapsed{ 0.f };
	float loopWaitElapsed{ 0.f };
	float firstRunElapsed{ 0.f };
public:
	Animator* owner;
public:
	AnimSet(Animator* owner_);
	~AnimSet();

	bool currLoopWaits();
	bool currPlaying();
	bool currLoops();
	bool currIsLoopWaiting();
	float currLoopWaitDelay();
	float  currFrameDelay();
	sf::IntRect currFrame();
	std::unordered_map<std::string, std::unordered_map<std::string, Animation>>& getAnims();
	void addAnimation(std::string id_, int numFrames_ = 1, sf::Vector2f frameSize_ = sf::Vector2f{ 50.f,50.f }, sf::Vector2f startPixel_ = sf::Vector2f{ 0.f,0.f }, float frameDelay_ = { 0.13f }, std::string dirType_ = "Uni", bool genOtherDirection = false, bool loops_ = true, bool loopWaits_ = false, float loopDelay_ = 0.f, sf::Vector2f texOffset_ = { 0.f,0.f }, sf::Vector2f bboxSize_ = { 0.f,0.f });
	bool checkIfHasTransition(std::string toAnim_);
	void setTransBuffer(std::string toAnim_);
	void updateCurrentAnim();
	bool isTransitioning();
	void animate(float gameTime_);
	void start();
	void pause();
	void play();
	void stop();
	Animation& getAnimation(std::string id_, std::string direction_)
	{
		auto found = anims.find(id_);
		if (found == anims.end())
		{
			std::cout << id_ << " is not an animation an an entity you are calling it for" << std::endl;
			return anims["Default"].at("Uni");
		}
		auto found2 = anims[id_].find(direction_);
		if (found2 == anims[id_].end())
		{
			std::cout << direction_ << " is not a direction this entity has stored" << std::endl;
			return anims["Default"].at("Uni");
		}
		return anims[id_].at(direction_);
	}
	std::string getCurrAnimationID()
	{
		return getCurrAnimation().getID();
	}
	Animation& getCurrAnimation()
	{
		auto found = anims.find(currentAnim);
		if (found == anims.end())
		{
			std::cout << currentAnim << " is not an animation an an entity you are calling it for" << std::endl;
			return anims["Default"].at("Uni");
		}
		auto found2 = anims[currentAnim].find(currDir);
		if (found2 == anims[currentAnim].end())
		{
			std::cout << currDir << " is not a direction this entity has stored" << std::endl;
			return anims["Default"].at("Uni");
		}		
		// else both currentAnim and currDir is acceptable, lets pull it out and return it
		return anims[currentAnim].at(currDir);
	}
};

#endif