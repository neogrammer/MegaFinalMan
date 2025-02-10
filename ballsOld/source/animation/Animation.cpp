#include "Animation.h"

Animation::Animation(std::string id_, std::string dir_, float frameDelay_, unsigned numFrames_ ,sf::Vector2f frameSize_, sf::Vector2f texStartPos_)
	: id{id_}
	, dirType{dir_}
	, frameDelay{frameDelay_}
	, loopDelay{0.f}
	, firstDelay{0.f}
	, numFrames{numFrames_}
	, frameSize{frameSize_}
	, rects{}
	, texStartPos{texStartPos_}
{
	rects.clear();
	rects.reserve(numFrames_);

	for (int i = 0; i < numFrames_; i++)
	{
		auto tmp = sf::IntRect(texStartPos_.x + i*frameSize_.x,texStartPos_.y,frameSize_.x,frameSize_.y);
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
