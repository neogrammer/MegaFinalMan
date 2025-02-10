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

void Animator::addAnim(std::string id_, int numFrames_, sf::Vector2f frameSize_, float frameDelay_, sf::Vector2f startPixel_, std::string dirType_, bool genOtherDirection_)
{
	animSet.addAnimation(id_, numFrames_, frameSize_, startPixel_, frameDelay_, dirType_, genOtherDirection_);
	if (this->animSet.getCurrAnimationID() == "Default")
	{
		this->animSet.setTransBuffer(id_);
		this->animSet.updateCurrentAnim();
	}
}

