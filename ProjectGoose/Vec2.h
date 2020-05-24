#pragma once

#include <cmath>
#include <SFML/System.hpp>

template<typename T>
class Vec2
{
public:
	Vec2() : x(T(0)), y(T(0)) {}
	Vec2(T in_x, T in_y) : x(in_x), y(in_y) {}
	Vec2 Normalize()
	{
		T length = Length();
		if (length != 0.0f)
		{
			x /= length;
			y /= length;
		}
		return *this;
	}
	T Length() const
	{
		return std::sqrt(x * x + y * y);
	}
	Vec2 operator*(T scalar) const
	{
		return Vec2(x * scalar, y * scalar);
	}
	operator sf::Vector2<T>() const
	{
		return { x, y };
	}
	T x;
	T y;
};

typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;