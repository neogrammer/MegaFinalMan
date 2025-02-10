#pragma once
#include <misc/BBox.h>

class Frame
{
public:
	Frame()=default;
	~Frame() = default;
	Frame(const Frame&) = default;
	Frame(Frame&&) = default;
	Frame& operator=(const Frame&) = default;
	Frame& operator=(Frame&&) = default;

	sf::Vector2f texOffset{};
	sf::IntRect texRect{};
	sf::Texture* texture{};
};