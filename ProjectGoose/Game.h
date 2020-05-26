#pragma once

#include <SFML/Graphics.hpp>

#include "Goose.h"
#include "ScrollingBackground.h"
#include "ResourceHolder.h"
#include "Zombie.h"
#include "ZombieSpawner.h"

class Game
{
public:
	Game(sf::RenderWindow& window);
	void Go();
private:
	void Update();
	void Draw();
	void SetWindowView();
	void DetectCollisions();
private:
	sf::RenderWindow& wnd;

	// Game variables
	sf::Clock frameTimer;
	float dt = 0.0f;
	ResourceHolder resourceHolder;
	Goose player;
	ScrollingBackground background;
	ZombieSpawner zombieSpawner;
	float collisionCheckInterval = 1.0f / 24.0f; // check for collision 24 times a second
	float timeSinceLastCheckedCollision = std::numeric_limits<float>::max();
};