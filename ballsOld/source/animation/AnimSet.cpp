#include "AnimSet.h"
#include <iostream>
AnimSet::AnimSet()
	: animMap{}
	, animTransMap{}
{
	animMap.clear();
	animMap.emplace(std::pair{ "Default", std::vector<Animation>{} });
	animMap["Default"].clear();
	animMap["Default"].push_back(Animation{"Default", "Uni"});
	animMap["Default"].push_back(Animation{ "Default", "Left" });
	animMap["Default"].push_back(Animation{ "Default", "Right" });

	animTransMap.clear();
}

AnimSet::~AnimSet()
{
}

void AnimSet::addAnimation(std::string id_, int numFrames_, sf::Vector2f frameSize_, sf::Vector2f startPixel_, float frameDelay_, std::string dirType_, bool genOtherDirection)
{
	auto found = animMap.find(id_);
	if (found != animMap.end())
	{
		std::cout << "Just tried to add another animation with the same name to the same animset" << std::endl;
		return;
	}
	// assume that animation needs to be created
	animMap[id_] = std::vector<Animation>{};
	animMap[id_].push_back(Animation{id_, dirType_, frameDelay_, (unsigned int)numFrames_, frameSize_, startPixel_});
}

bool AnimSet::checkIfHasTransition(std::string toAnim_)
{
	auto found = animTransMap.find(toAnim_);
	if (found == animTransMap.end())
	{
		// animation not in the transition map, let's leave returning false
		return false;
	}
	// else return true back to caller
	return true;
}

void AnimSet::setTransBuffer(std::string toAnim_)
{
	auto found = animMap.find(toAnim_);
	if (found != animMap.end())
	{
		transBuffer = toAnim_;
		transitioning = true;
	}
	else
	{
		std::cout << "Animation not in animMap yet!" << std::endl;
	}
}

void AnimSet::updateCurrentAnim()
{
	if (transitioning)
	{
		currentAnim = transBuffer;

		// no longer transitioning, set back to begin frame state for next iteration of main loop
		transitioning = false;
		transBuffer = "None";
	}
	else
	{
		//else leave it as it is
		if (transBuffer != "None")
		{
			std::cout << "Transbuffer has an action that is not updating the currentAnim at the end of the frame loop" << std::endl;
		}
	}
}

bool AnimSet::isTransitioning()
{
	return transitioning;
}




