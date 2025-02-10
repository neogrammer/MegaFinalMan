#ifndef ANIM_SET_H__
#define ANIM_SET_H__
#include <vector>
#include <string>
#include <unordered_map>
#include "Animation.h"
class AnimSet
{
	friend class Animator;
	std::unordered_map<std::string, std::vector<Animation>> animMap; // id stored Animations
	std::unordered_map<std::string, std::vector<std::string>> animTransMap; // each id is a key, and the value is a vector of animation ids the key can transition to

	std::string transBuffer{"None"};  //  None indicates no transition has occured this frame, so start each frame at None;
	 // during a frame, transitions can occur that change the state multiple times , change this
	std::string currentAnim{"Default"}; // at end of frame every loop end, set this to transBuffer, as it was able to get through those transitions then the new
	 // currentAnim should reflect the new animation next frame
	std::string currDir{ "Uni" };
	unsigned int frameIdx{ 0U }; // keep track of animations with higher level frameIdx, meaning, you must flush this back to zero when switching animations
	// and be careful not to exceed the max frame in the vector
	unsigned int currMaxIdx{ 0U };

	bool transitioning{ false };
public:
	AnimSet();
	~AnimSet();

	void addAnimation(std::string id_, int numFrames_ = 1, sf::Vector2f frameSize_ = sf::Vector2f{ 50.f,50.f }, sf::Vector2f startPixel_ = sf::Vector2f{ 0.f,0.f }, float frameDelay_ = { 0.13f }, std::string dirType_ = "Uni", bool genOtherDirection = false);
	bool checkIfHasTransition(std::string toAnim_);
	void setTransBuffer(std::string toAnim_);
	void updateCurrentAnim();
	bool isTransitioning();
	Animation& getAnimation(std::string id_, std::string direction_)
	{
		// "Uni == 0, Left == 1, Right == 2"

		if (direction_ == "Uni")
			return animMap.at(id_)[0];
		else if (direction_ == "Left")
			return animMap.at(id_)[1];
		else if (direction_ == "Right")
			return animMap.at(id_)[2];
		else
			throw std::runtime_error("Shit, trying to get a nonexistant animation!");
	}
	std::string getCurrAnimationID()
	{
		return getCurrAnimation().getID();
	}
	Animation& getCurrAnimation()
	{
		// TODO: insert return statement 
		auto& v = animMap.at(currentAnim);
		if (currDir == "Uni")
			return v.at(0);
		else if (currDir == "Left")
			return v.at(1);
		else if (currDir == "Right")
			return v.at(2);
		else
			std::runtime_error(R"(Shit, getCurrentAnimation() using non valid animation)");
	}
	
};

#endif