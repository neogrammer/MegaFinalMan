#include "Animation.h"

Animation::Animation(std::string id_, std::string dir_, float frameDelay_, unsigned numFrames_ ,sf::Vector2f frameSize_, sf::Vector2f texStartPos_
 , bool loops_ , bool loopWaits_ , float loopDelay_)
	: id{id_}
	, dirType{dir_}
	, frameDelay{frameDelay_}
	, loopDelay{0.f}
	, firstDelay{0.f}
	, numFrames{numFrames_}
	, frameSize{frameSize_}
	, rects{}
	, texStartPos{texStartPos_}
	, loops{loops_}
	, loopWaits{loopWaits_}
{
	rects.clear();
	rects.reserve(numFrames_);

	for (unsigned int i = 0; i < numFrames_; i++)
	{
		sf::IntRect tmp = sf::IntRect((int)texStartPos_.x + (int)i*(int)frameSize_.x,(int)texStartPos_.y,(int)frameSize_.x,(int)frameSize_.y);
		rects.push_back(tmp);
	}
}

Animation::~Animation()
{
}

std::string Animation::getDirType()
{
	return dirType;
}

std::string Animation::getID()
{
	return id;
}

sf::Vector2f Animation::getFrameSize()
{
	return frameSize;
}

sf::IntRect Animation::getFrame(int index)
{
	return rects[index];
}

float Animation::getFrameDelay()
{
	return frameDelay;
}

float Animation::getLoopDelay()
{
	return loopDelay;
}

bool Animation::isLooping()
{
	return this->loops;
}

bool Animation::doesLoopWait()
{
	return loopWaits;;
}

void Animation::setDirType(std::string type_)
{
	dirType = type_;
}

std::vector<sf::IntRect>& Animation::getRects()
{
	return rects;
}

sf::IntRect Animation::getRect(int index_)
{
	return rects[index_];
}

int Animation::getNumFrames()
{
	return numFrames;
}
