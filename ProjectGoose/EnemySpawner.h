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

	EnemySpawner(const EnemySpawnBehavior& spawnBehavior);
	void Update(float dt);
	static void UpdateAllEnemies(float dt);
	static void DrawEnemies(sf::RenderTarget& target);
	void SetSpawnPosition(sf::Vector2f position) { spawnBehavior.prototype->SetPosition(position); }
	static auto& GetEnemies() { 
		static std::vector<std::unique_ptr<Enemy>> allEnemies;
		return allEnemies; 
	}
private:
	void SpawnEnemy();
private:
	EnemySpawnBehavior spawnBehavior;
	float timeSinceLastSpawnedEnemy;
};