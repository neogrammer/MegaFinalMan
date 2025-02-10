#include <misc/v2.h>
#include <corecrt_math.h>

v2 v2::norm() const
{
	return v2(this->x / this->length(), this->y / this->length());
}


float v2::dot(const v2& rhs_) const
{
	return (this->x * rhs_.x + this->y * rhs_.y);
}

v2 v2::mul(const v2& rhs_) const
{
	return v2(this->x * rhs_.x, this->y * rhs_.y);
}


float v2::length() const
{
	return sqrtf(powf(this->x,2) + powf(this->y, 2));
}

v2 v2::to(const v2& head_) const
{
	return v2(head_.x - this->x, head_.y - this->y);
}

v2 v2::from(const v2& tail_) const
{
	return v2(this->x - tail_.x, this->y - tail_.y);
}

v2 v2::divideBy(const v2& other)
{
	v2 tmp{ 0.f,0.f };
	tmp.x = this->x / other.x;
	tmp.y = this->y / other.y;
	return tmp;
}
