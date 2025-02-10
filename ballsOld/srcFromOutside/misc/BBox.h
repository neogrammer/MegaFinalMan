#pragma once
#include <misc/v2.h>
#include <SFML/Graphics.hpp>
// magical box to keep track of the actual sprite in game bounds to be used
// with velocity
class BBox
{
public:

	BBox(const v2& size_ = { 0.f,0.f });
	~BBox() = default;
	BBox(const BBox&) = default;
	BBox(BBox&&) = default;
	BBox& operator=(const BBox&) = default;
	BBox& operator=(BBox&&) = default;
	v2 sz{};


	float hw();
	float hh();




};