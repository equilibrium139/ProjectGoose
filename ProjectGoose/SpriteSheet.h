#pragma once

#include <SFML/Graphics.hpp>

struct SpriteSheet
{
public:
	SpriteSheet(const sf::Texture& sheet, int nFrames, int rows, int columns)
		:sheet(sheet), nFrames(nFrames), rows(rows), columns(columns)
	{}
	const sf::Texture& sheet;
	const int nFrames;
	const int rows;
	const int columns;
};