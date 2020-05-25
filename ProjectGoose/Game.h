#pragma once

#include <SFML/Graphics.hpp>

#include "Goose.h"
#include "ScrollingBackground.h"
#include "ResourceHolder.h"
#include "Zombie.h"

class Game
{
public:
	Game(sf::RenderWindow& window);
	void Go();
private:
	void Update();
	void Draw();
	void SetWindowView();
private:
	sf::RenderWindow& wnd;

	// Game variables
	sf::Clock frameTimer;
	float dt = 0.0f;
	ResourceHolder resourceHolder;
	Goose player;
	ScrollingBackground background;
	Zombie zombie;
};