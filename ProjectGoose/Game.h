#pragma once

#include <SFML/Graphics.hpp>

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
};