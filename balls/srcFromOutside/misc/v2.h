#pragma once
#include <SFML/System/Vector2.hpp>

class v2 : public sf::Vector2f
{
public:
	using sf::Vector2f::Vector2f;
	v2(const v2&)=default;
	v2& operator=(const v2&) = default;
	v2 norm() const;
	float dot(const v2& rhs_) const;
	v2 mul(const v2& rhs_) const;
	float length() const;
	v2 to(const v2& head_) const;
	v2 from(const v2& head_) const;
	
	v2 divideBy(const v2& other);
};
