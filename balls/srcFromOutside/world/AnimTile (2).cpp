#include <misc/Animation.h>
#include "AnimTile.h"
#include <iostream>

void AnimTile::loadAnimation(std::string name_, sf::Texture& tex_, int numFrames_, std::vector<v2> offsets_, std::vector<v2> bboxes_, v2 frameSize_, v2 startPixel)
{

	if (anims.find(name_) != anims.end())
	{
		std::cout << "Anim already in place" << std::endl;
		return;
	}
	else
	{
		anims.emplace(name_, Animation{});
		anims.at(name_).loadFrames(frameSize_, offsets_, tex_, numFrames_, startPixel);
		bboxes.emplace(name_, std::vector<BBox>{});
		bboxes[name_].clear();
		bboxes[name_].reserve(numFrames_);
		for (int i = 0; i < numFrames_; i++)
		{
			bboxes[name_].emplace_back(bboxes_[i]);
		}
		if (currAnim == "default")
			currAnim = name_;


		return;
	}
	return;
}
