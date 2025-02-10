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

void AnimSet::addAnimation(std::string id_, int numFrames_, sf::Vector2f frameSize_, sf::Vector2f startPixel_, float frameDelay_, std::string dirType_, bool genOtherDirection, bool loops_, bool loopWaits_, float loopDelay_)
{
	auto found = animMap.find(id_);
	if (found != animMap.end())
	{
		if (found->second.size() != 3)
		{
			animMap[id_].emplace_back(std::move(Animation{ id_, "Uni" }));
			animMap[id_].emplace_back(std::move(Animation{ id_, "Left" }));
			animMap[id_].emplace_back(std::move(Animation{ id_, "Right" }));
		}

		std::cout << "replacing an animation already setup or defaulted" << std::endl;
		auto iter = animMap[id_].begin();
		for (int i = 0; i < 3; i++)
		{
			if (dirType_ == iter->getDirType())
			{
				//found it, replace it
				animMap[id_].erase(iter);
				break;
			}

			iter++;


			// keep trying 
		}
		auto& an = animMap[id_].at((dirType_ == "Uni") ? 0 : (dirType_ == "Left") ? 1 : (dirType_ == "Right") ? 2 : 0) = std::move(Animation{ id_, dirType_, frameDelay_, (unsigned int)numFrames_, frameSize_, startPixel_, loops_, loopWaits_, loopDelay_ });
		auto& r = an.getRects();
		r[0] = { {(int)startPixel_.x,(int)startPixel_.y},{(int)frameSize_.x,(int)frameSize_.y} };
		for (int i=1; i < numFrames_; i++)
		{
			r.emplace_back(sf::IntRect{{(int)startPixel_.x + i * (int)frameSize_.x,(int)startPixel_.y},{(int)frameSize_.x,(int)frameSize_.y}});
		}
	}
	else
	{

		// assume that animation needs to be created
		animMap[id_] = std::vector<Animation>{};

		if (dirType_ == "Uni")
		{
			animMap[id_].emplace_back(std::move(Animation{ id_, "Uni", frameDelay_, (unsigned int)numFrames_, frameSize_, startPixel_, loops_, loopWaits_, loopDelay_ }));
			auto& an = animMap[id_].at((dirType_ == "Uni") ? 0 : (dirType_ == "Left") ? 1 : (dirType_ == "Right") ? 2 : 0) = std::move(Animation{ id_, dirType_, frameDelay_, (unsigned int)numFrames_, frameSize_, startPixel_, loops_, loopWaits_, loopDelay_ });
			auto& r = an.getRects();
			r[0] = { {(int)startPixel_.x,(int)startPixel_.y},{(int)frameSize_.x,(int)frameSize_.y} };
			for (int i = 1; i < numFrames_; i++)
			{
				r.emplace_back(sf::IntRect{ {(int)startPixel_.x + i * (int)frameSize_.x,(int)startPixel_.y},{(int)frameSize_.x,(int)frameSize_.y} });
			}
			animMap[id_].emplace_back(std::move(Animation{ id_, "Left" }));
			animMap[id_].emplace_back(std::move(Animation{ id_, "Right" }));

		}
		else if (dirType_ == "Left")
		{
			animMap[id_].emplace_back(std::move(Animation{ id_, "Uni" }));
			animMap[id_].emplace_back(std::move(Animation{ id_, "Left", frameDelay_, (unsigned int)numFrames_, frameSize_, startPixel_, loops_, loopWaits_, loopDelay_ }));
			auto& an = animMap[id_].at((dirType_ == "Uni") ? 0 : (dirType_ == "Left") ? 1 : (dirType_ == "Right") ? 2 : 0) = std::move(Animation{ id_, dirType_, frameDelay_, (unsigned int)numFrames_, frameSize_, startPixel_, loops_, loopWaits_, loopDelay_ });
			auto& r = an.getRects();
			r[0] = { {(int)startPixel_.x,(int)startPixel_.y},{(int)frameSize_.x,(int)frameSize_.y} };
			for (int i = 1; i < numFrames_; i++)
			{
				r.emplace_back(sf::IntRect{ {(int)startPixel_.x + i * (int)frameSize_.x,(int)startPixel_.y},{(int)frameSize_.x,(int)frameSize_.y} });
			}
			animMap[id_].emplace_back(std::move(Animation{ id_, "Right" }));

		}
		else
		{
			animMap[id_].emplace_back(std::move(Animation{ id_, "Uni" }));

			animMap[id_].emplace_back(std::move(Animation{ id_, "Left" }));
			animMap[id_].emplace_back(std::move(Animation{ id_, "Right", frameDelay_, (unsigned int)numFrames_, frameSize_, startPixel_, loops_, loopWaits_, loopDelay_ }));
			auto& an = animMap[id_].at((dirType_ == "Uni") ? 0 : (dirType_ == "Left") ? 1 : (dirType_ == "Right") ? 2 : 0) = std::move(Animation{ id_, dirType_, frameDelay_, (unsigned int)numFrames_, frameSize_, startPixel_, loops_, loopWaits_, loopDelay_ });
			auto& r = an.getRects();
			r[0] = { {(int)startPixel_.x,(int)startPixel_.y},{(int)frameSize_.x,(int)frameSize_.y} };
			for (int i = 1; i < numFrames_; i++)
			{
				r.emplace_back(sf::IntRect{ {(int)startPixel_.x + i * (int)frameSize_.x,(int)startPixel_.y},{(int)frameSize_.x,(int)frameSize_.y} });
			}
		}
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

void AnimSet::animate(float gameTime_)
{
	if (playing)
	{
			if (loopWaiting)
			{
				// wait for loop waiting
				loopWaitElapsed += gameTime_;

				if (loopWaitElapsed > getCurrAnimation().getLoopDelay())
				{
					loopWaiting = false;
					loopWaitElapsed = 0.f;
					frameIdx = 0;
					frameElapsed = 0.f;
				}
			}
			else
			{
				frameElapsed += gameTime_;

				if (frameElapsed > animMap.at(currentAnim).at((currDir == "Uni") ? 0 : (currDir == "Left") ? 1 : (currDir == "Right") ? 2 : 0).getFrameDelay())
				{

					frameElapsed = 0.f;
					frameIdx++;

					if ((int)frameIdx >= animMap.at(currentAnim).at((currDir == "Uni") ? 0 : (currDir == "Left") ? 1 : (currDir == "Right") ? 2 : 0).getNumFrames())
					{
						if (this->getCurrAnimation().isLooping())
						{
							if (this->getCurrAnimation().doesLoopWait())
							{
								frameIdx = animMap.at(currentAnim).at((currDir == "Uni") ? 0 : (currDir == "Left") ? 1 : (currDir == "Right") ? 2 : 0).getNumFrames() - 1;
								loopWaitElapsed = 0.f;
								loopWaiting = true;
							}
							else
							{
								frameIdx = 0;
							}
						}
						else
						{
							
							frameIdx = animMap.at(currentAnim).at((currDir == "Uni") ? 0 : (currDir == "Left") ? 1 : (currDir == "Right") ? 2 : 0).getNumFrames() - 1;
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




