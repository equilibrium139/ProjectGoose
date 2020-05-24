#pragma once

#include <SFML/Graphics.hpp>

#include "Goose.h"
#include "ScrollingBackground.h"

class Game
{
public:
	Game(sf::RenderWindow& window);
	void Go();
private:
	void Update();
	void Draw();
private:
	sf::RenderWindow& wnd;

	// Game variables
	sf::Clock frameTimer;
	float dt = 0.0f;
	Goose player;
	ScrollingBackground background;
};