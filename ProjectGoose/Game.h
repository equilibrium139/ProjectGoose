#pragma once

#include <SFML/Graphics.hpp>

#include "Goose.h"
#include "ScrollingBackground.h"
#include "ResourceHolder.h"
#include "Zombie.h"
#include "EnemySpawner.h"
#include "Button.h"

class Game
{
public:
	Game(sf::RenderWindow& window);
	void Go();
	enum class Level
	{
		Menu,
		Level1,
		NLEVELS
	};
private:
	void Update();
	void Draw();
	void SetWindowView();
	void DetectCollisions();
private:
	sf::RenderWindow& wnd;

	sf::Music backgroundMusic;
	sf::Clock frameTimer;
	float dt = 0.0f;
	Goose player;
	ScrollingBackground background;
	sf::Texture& loseBackgroundTexture;
	sf::Sprite loseBackground;
	std::vector<EnemySpawner> enemySpawners;
	float collisionCheckInterval = 1.0f / 24.0f; // check for collision 24 times a second
	float timeSinceLastCheckedCollision = std::numeric_limits<float>::max();
	bool gameStarted = false;
	Button play;
};