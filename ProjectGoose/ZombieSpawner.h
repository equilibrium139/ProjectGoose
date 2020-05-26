#pragma once

#include <vector>

#include <SFML/System.hpp>

#include "ResourceHolder.h"
#include "Zombie.h"

class ZombieSpawner
{
public:
	ZombieSpawner(ResourceHolder& resourceHolder, const sf::RenderWindow& window, sf::Vector2f spawnPos = sf::Vector2f(0.0f, 0.0f));
	void Update(float dt);
	void DrawZombies(sf::RenderTarget& target);
	void SetSpawnPosition(sf::Vector2f position) { spawnPosition = position; }
	const std::vector<Zombie>& GetZombies() { return zombies; }
private:
	void SpawnZombie();
private:
	float spawnInterval = 5.0f;
	float timeSinceLastSpawned;
	sf::Vector2f spawnPosition;
	ResourceHolder& resourceHolder;
	const sf::RenderWindow& window;
	std::vector<Zombie> zombies;
};