#include <misc/BBox.h>

BBox::BBox(const v2& size_)
: sz{size_}
{
}

float BBox::hw()
{
	return sz.x / 2.f;
}

float BBox::hh()
{
	return sz.y / 2.f;
}

