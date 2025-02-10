#include "AnimSet.h"
#include <iostream>
#include "Animator.h"
#include "../physics/RigidBody.h"
#include "../objects/DynamicObject.h"
AnimSet::AnimSet(Animator* owner_)
	: anims{}
	, animTransMap{}
	, owner{owner_}
{
	anims.clear();
	anims.emplace(std::pair{ "Default", std::unordered_map<std::string,Animation>{} });
	anims["Default"].emplace(std::pair<std::string, Animation>{"Uni", Animation{}});


	animTransMap.clear();
}

AnimSet::~AnimSet()
{
}

bool AnimSet::currLoopWaits()
{
	return getCurrAnimation().doesLoopWait();
}

bool AnimSet::currPlaying()
{
	return playing;
}

bool AnimSet::currLoops()
{
	return getCurrAnimation().isLooping();
}

bool AnimSet::currIsLoopWaiting()
{
	return getCurrAnimation().isLoopWaiting();
}

float AnimSet::currLoopWaitDelay()
{
	return getCurrAnimation().getLoopDelay();
}

float AnimSet::currFrameDelay()
{
	return getCurrAnimation().getFrameDelay();
}

sf::IntRect AnimSet::currFrame()
{
	if (frameIdx >= getCurrAnimation().getRects().size())
	{
		std::cout << "frame index was out of range, setting to zero" << std::endl;
		frameIdx = 0;
	}
	return getCurrAnimation().getRects().at(frameIdx);
}

std::unordered_map<std::string, std::unordered_map<std::string, Animation>>& AnimSet::getAnims()
{
	return anims;
}

void AnimSet::addAnimation(std::string id_, int numFrames_, sf::Vector2f frameSize_, sf::Vector2f startPixel_, float frameDelay_, std::string dirType_, bool genOtherDirection, bool loops_, bool loopWaits_, float loopDelay_, sf::Vector2f texOffset_, sf::Vector2f bboxSize_)
{
	
	auto found = anims.find(id_);
	if (found != anims.end())
	{
		auto found2 = anims[id_].find(dirType_);
		if (found2 != anims[id_].end())
		{
			std::cout << dirType_ << "already in the entity for animation " << id_ << ", overwriting with new data" << std::endl;
		}
		
		anims.at(id_)[dirType_] = Animation{ id_, dirType_, frameDelay_, (unsigned int)numFrames_, frameSize_, startPixel_, loops_, loopWaits_, loopDelay_ };
	}
	else
	{
		anims[id_] = std::unordered_map<std::string, Animation>{};
		anims.at(id_)[dirType_] = Animation{ id_, dirType_, frameDelay_, (unsigned int)numFrames_, frameSize_, startPixel_, loops_, loopWaits_, loopDelay_ };
		
	}
	auto& currAnim = owner->owner->getRigid().aabb[id_];
	currAnim.emplace(std::pair<std::string, std::vector<BoundingBox> >{dirType_, std::vector<BoundingBox>{}});

	if (bboxSize_ == sf::Vector2f{ 0.f, 0.f })
	{
		bboxSize_ = { frameSize_ };
	}
	for (int i = 0; i < numFrames_; i++)
	{
		currAnim[dirType_].emplace_back(BoundingBox{ bboxSize_.x, bboxSize_.y, texOffset_.x, texOffset_.y });
	}
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
	auto found = anims.find(toAnim_);
	if (found != anims.end())
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

void AnimSet::animate(float gameTime_)
{
	if (playing)
	{
			if (this->currIsLoopWaiting())
			{
				// wait for loop waiting
				loopWaitElapsed += gameTime_;

				if (loopWaitElapsed > this->currLoopWaitDelay())
				{
					getCurrAnimation().setIsLoopWaiting(false);
					loopWaitElapsed = 0.f;
					frameIdx = 0;
					frameElapsed = 0.f;
				}
			}
			else
			{
				frameElapsed += gameTime_;
				Animation* anim{ nullptr };
				for (auto& an : anims.at(currentAnim))
				{
					if (an.second.getDirType() == currDir)
					{
						anim = &an.second;
					}
				}
				if (anim == nullptr)
				{
					return;
				}
				else
				{
					if (frameElapsed > anim->getFrameDelay())
					{
						frameElapsed = 0.f;
						frameIdx++;
						if ((int)frameIdx >= anim->getNumFrames())
						{
							if (anim->isLooping())
							{
								if (anim->doesLoopWait())
								{
									frameIdx = anim->getNumFrames() - 1;
									loopWaitElapsed = 0.f;
									getCurrAnimation().setIsLoopWaiting(true);
								}
								else
								{
									frameIdx = 0;
								}
							}
							else
							{
								frameIdx = anim->getNumFrames() - 1;
							}
						}
					}
				}
			}
	}
}

void AnimSet::start()
{
	frameIdx = 0;
	playing = true;
	frameElapsed = 0.f;
}

void AnimSet::pause()
{
	playing = false;
}

void AnimSet::play()
{
	playing = true;
	frameElapsed = 0.f;
}

void AnimSet::stop()
{
	playing = false;
	frameIdx = 0;
}




