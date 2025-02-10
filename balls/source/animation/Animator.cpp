#include "Animator.h"

Animator::Animator()
	: animSet{}
{
}

Animator::~Animator()
{
}

sf::IntRect Animator::getFrame()
{
	return animSet.getCurrAnimation().getFrame(animSet.frameIdx);
}

sf::Vector2f Animator::getFrameSize()
{
	return animSet.getCurrAnimation().getFrameSize();
}

void Animator::addAnim(std::string id_, int numFrames_, sf::Vector2f frameSize_, float frameDelay_, sf::Vector2f startPixel_, std::string dirType_, bool genOtherDirection_, bool loops_, bool loopWaits_, float loopDelay_)
{
	if (animSet.animMap[id_].size() != 3)
	{
		animSet.addAnimation(id_);
		animSet.addAnimation(id_);
		animSet.addAnimation(id_);
		animSet.animMap[id_].at(0).setDirType("Uni");
		animSet.animMap[id_].at(1).setDirType("Left");
		animSet.animMap[id_].at(2).setDirType("Right");

	}
	else
	{
		animSet.addAnimation(id_, numFrames_, frameSize_, startPixel_, frameDelay_, dirType_, genOtherDirection_, loops_, loopWaits_, loopDelay_);
	}
	animSet.addAnimation(id_, numFrames_, frameSize_, startPixel_, frameDelay_, dirType_, genOtherDirection_, loops_, loopWaits_, loopDelay_);
	

	if (this->animSet.getCurrAnimationID() == "Default")
	{
		this->animSet.setTransBuffer(id_);
		this->animSet.updateCurrentAnim();
	}


}

void Animator::update(float gameTime_)
{
	animSet.animate(gameTime_);
}

