#pragma once

#include <memory>
#include <vector>

#include <SFML/System.hpp>

#include "ResourceHolder.h"
#include "Enemy.h"

//Class for spawning and managing minion zombies and giant zombies
class EnemySpawner
{
public:

	struct EnemySpawnBehavior
	{
		EnemySpawnBehavior(Enemy* proto, float spawnInterval = 3.0f,
			float spawnStartTime = 0.0f)
			:prototype(proto), spawnInterval(spawnInterval), spawnStartTime(spawnStartTime) {}
		Enemy* prototype;
		float spawnInterval = 3.0f;
		float spawnStartTime = 0.0f;
	};

	EnemySpawner(const EnemySpawnBehavior& minionSpawnBehavior, const EnemySpawnBehavior& giantSpawnBevaior);
	void Update(float dt);
	void DrawEnemies(sf::RenderTarget& target);
	void SetMinionSpawnPosition(sf::Vector2f position) { minionSpawnBehavior.prototype->SetPosition(position); }
	void SetGiantSpawnPosition(sf::Vector2f position) { giantSpawnBehavior.prototype->SetPosition(position); }
	auto& GetEnemies() { return enemies; }
private:
	void SpawnEnemy(const EnemySpawnBehavior& spawnBehavior);
private:
	EnemySpawnBehavior minionSpawnBehavior;
	EnemySpawnBehavior giantSpawnBehavior;
	float timeSinceLastSpawnedMinion;
	float timeSinceLastSpawnedGiant;
	std::vector<std::unique_ptr<Enemy>> enemies;
};