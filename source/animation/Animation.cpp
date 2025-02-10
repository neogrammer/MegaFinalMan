#include "Animation.h"
#include <iostream>
Animation::Animation(std::string id_, std::string dir_, float frameDelay_, unsigned numFrames_ ,sf::Vector2f frameSize_, sf::Vector2f texStartPos_
 , bool loops_ , bool loopWaits_ , float loopDelay_, sf::Vector2f texOff_)
	: id{id_}
	, dirType{dir_}
	, frameDelay{frameDelay_}
	, loopDelay{ loopDelay_ }
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
	texOffsets.clear();
	texOffsets.reserve(numFrames_);

	for (unsigned int i = 0; i < numFrames_; i++)
	{
		sf::IntRect tmp = sf::IntRect((int)texStartPos_.x + (int)i*(int)frameSize_.x,(int)texStartPos_.y,(int)frameSize_.x,(int)frameSize_.y);
		rects.push_back(tmp);
		texOffsets.emplace_back(sf::Vector2f{texOff_.x, texOff_.y});
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
	if (index >= rects.size())
		index = 0;
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

std::vector<sf::Vector2f>& Animation::getTexOffsets()
{
	return texOffsets;
}

sf::Vector2f Animation::getTexOffset(int index_)
{
	if (index_ >= texOffsets.size())
	{
		std::cout << "texOffset for current animation does not exist" << std::endl;
		return sf::Vector2f{ 0.f,0.f };
	}
	return texOffsets.at(index_);
}

std::vector<sf::IntRect>& Animation::getRects()
{
	return rects;
}

sf::IntRect Animation::getRect(int index_)
{
	if (index_ >= rects.size()) { return rects[rects.size() - 1]; }
	return rects[index_];
}

bool Animation::isLoopWaiting()
{
	return loopWaiting;
}

void Animation::setIsLoopWaiting(bool cond_)
{
	loopWaiting = cond_;
}

int Animation::getNumFrames()
{
	return numFrames;
}
