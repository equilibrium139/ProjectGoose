#pragma once

#include <cmath>
#include <SFML/System.hpp>

template<typename T>
T Length(const sf::Vector2<T>& vec)
{
	return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

template<typename T>
void Normalize(sf::Vector2<T>& vec)
{
	T length = Length(vec);
	if (length != 0.0f)
	{
		vec.x /= length;
		vec.y /= length;
	}
}

template<typename T>
sf::Vector2<T> GetNormalized(const sf::Vector2<T>& vec)
{
	auto normalized = vec;
	Normalize(normalized);
	return normalized;
}