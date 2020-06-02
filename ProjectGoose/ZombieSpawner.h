#pragma once

#include <memory>
#include <vector>

#include <SFML/System.hpp>

#include "ResourceHolder.h"
#include "Zombie.h"

//Class for spawning and managing minion zombies and giant zombies
class ZombieSpawner
{
public:

	struct ZombieSpawnBehavior
	{
		sf::Vector2f spawnPos = sf::Vector2f(0.0f, 0.0f);
		float spawnInterval = 3.0f;
		float minionSpawnStartTime = 0.0f;
		float scale = 0.15f; 
		float speed = 150.0f;
		int hitpoints = 1;
	};

	ZombieSpawner(const sf::Vector2f& playerPosition, const ZombieSpawnBehavior& minionSpawnBehavior, const ZombieSpawnBehavior& giantSpawnBevaior);
	void Update(float dt);
	void DrawZombies(sf::RenderTarget& target);
	void SetMinionSpawnPosition(sf::Vector2f position) { minionSpawnBehavior.spawnPos = position; }
	void SetGiantSpawnPosition(sf::Vector2f position) { giantSpawnBehavior.spawnPos = position; }
	auto& GetZombies() { return zombies; }
private:
	void SpawnZombie(const ZombieSpawnBehavior& spawnBehavior);
private:
	const sf::Vector2f& playerPosition;
	ZombieSpawnBehavior minionSpawnBehavior;
	ZombieSpawnBehavior giantSpawnBehavior;
	float timeSinceLastSpawnedMinion;
	float timeSinceLastSpawnedGiant;
	std::vector<std::unique_ptr<Zombie>> zombies;
};