#include "Animator.h"
#include "../physics/RigidBody.h"
#include "../objects/DynamicObject.h"
Animator::Animator(DynamicObject* owner_)
	: animSet{this}
	, owner{owner_}
{
}

Animator::~Animator()
{
}

sf::IntRect Animator::getFrame()
{
	return animSet.getCurrAnimation().getFrame(animSet.frameIdx);
}

int Animator::getCurrIndex()
{
	return animSet.frameIdx;
}

sf::Vector2f Animator::getFrameSize()
{
	return animSet.getCurrAnimation().getFrameSize();
}

void Animator::addAnim( std::string id_, int numFrames_, sf::Vector2f frameSize_, float frameDelay_, sf::Vector2f startPixel_, std::string dirType_, bool genOtherDirection_, bool loops_, bool loopWaits_, float loopDelay_, sf::Vector2f texOffset_, sf::Vector2f bboxSize_)
{
	animSet.addAnimation(id_, numFrames_, frameSize_, startPixel_, frameDelay_, dirType_, genOtherDirection_, loops_, loopWaits_, loopDelay_, texOffset_, bboxSize_);

	if (this->animSet.getCurrAnimationID() == "Default")
	{
		this->animSet.currDir = dirType_;
		this->animSet.setTransBuffer(id_);
		this->animSet.updateCurrentAnim();
	}
}

AnimSet& Animator::getAnims()
{
	return animSet;
}

std::string Animator::getCurrID()
{
	return animSet.currentAnim;
}

std::string Animator::getCurrDir()
{
	return animSet.currDir;
}


void Animator::setCurrIndex(int idx_)
{
	animSet.frameIdx = idx_;
}

void Animator::update(float gameTime_)
{
	animSet.animate(gameTime_);
}

void Animator::setDir(std::string dir_)
{
	if (dir_ != "Uni" && dir_ != "Left" && dir_ != "Right")
		return;

	animSet.currDir = dir_;
}

