#pragma once

#include <memory>
#include <vector>

#include <SFML/System.hpp>

#include "ResourceHolder.h"
#include "Enemy.h"

//Class for spawning and managing enemies
class EnemySpawner
{
public:
	EnemySpawner(std::unique_ptr<Enemy>&& proto, float spawnInterval = 3.0f, float spawnStartTime = 0.0f);

	void Update(float dt);
	void SetSpawnPosition(sf::Vector2f position) { prototype->SetPosition(position); }

	static void UpdateAllEnemies(float dt);
	static void DrawEnemies(sf::RenderTarget& target);
	static auto& GetEnemies() { 
		static std::vector<std::unique_ptr<Enemy>> allEnemies;
		return allEnemies; 
	}
private:
	void SpawnEnemy();
private:
	std::unique_ptr<Enemy> prototype;
	float spawnInterval = 3.0f;
	float timeSinceLastSpawnedEnemy;
};