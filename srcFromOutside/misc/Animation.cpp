#include "Animation.h"
#include <assert.h>
void Animation::addFrame(sf::IntRect rect_, v2 offset_, sf::Texture& tex_)
{
	Frame tmp;
	tmp.texOffset = offset_;
	tmp.texture = &tex_;
	tmp.texRect = rect_;
	frames.push_back(tmp);
}

/// <summary>
/// // all animations should be on the same line in the texture to load properly
/// </summary>
/// <param name="size_"></param>
/// <param name="offsets_"></param>
/// <param name="tex_"></param>
/// <param name="numFrames_"></param>
/// <param name="startPixel_"></param>
void Animation::loadFrames(v2 size_, std::vector<v2> offsets_, sf::Texture& tex_, int numFrames_, v2 startPixel_)
{
	for (int i = 0; i < numFrames_; i++)
	{
		Frame tmp;
		tmp.texOffset = { offsets_[i].x, offsets_[i].y };
		tmp.texture = &tex_;
		sf::IntRect tmpRect;
		tmpRect.left = (int)(startPixel_.x + i * size_.x);
		tmpRect.top = (int)startPixel_.y;
		tmpRect.width = (int)size_.x;
		tmpRect.height = (int)size_.y;
		tmp.texRect = tmpRect;
		frames.push_back(tmp);
	}
	idx = 0;
	
}

Frame& Animation::frame()
{
	assert(idx < frames.size() && idx >= 0 && "index for animation is out of range");
	return frames.at(idx);
}

sf::IntRect Animation::rect()
{
	assert(idx < frames.size() && idx >= 0 && "index for animation is out of range");
	return frames[idx].texRect;
}
