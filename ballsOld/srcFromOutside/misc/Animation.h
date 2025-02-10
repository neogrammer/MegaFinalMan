#pragma once

#include <misc/Frame.h>
#include <vector>
class Animation
{
public:
	std::vector<Frame> frames{};
	int idx{};
	void addFrame(sf::IntRect rect_, v2 offset_, sf::Texture& tex_);
	void loadFrames(v2 size_, std::vector<v2> offsets_, sf::Texture& tex_, int numFrames_, v2 startPixel_);
	Frame& frame();
	sf::IntRect rect();


};