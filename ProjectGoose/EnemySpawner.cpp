#include "EnemySpawner.h"
#include <iostream>

EnemySpawner::EnemySpawner(const EnemySpawnBehavior& spawnBehavior)
	:spawnBehavior(spawnBehavior), 
	timeSinceLastSpawnedEnemy(spawnBehavior.spawnInterval - spawnBehavior.spawnStartTime)
{
}

void EnemySpawner::Update(float dt)
{
	timeSinceLastSpawnedEnemy += dt;
	if (timeSinceLastSpawnedEnemy >= spawnBehavior.spawnInterval)
	{
		SpawnEnemy();
		timeSinceLastSpawnedEnemy = 0.0f;
	}
}

void EnemySpawner::UpdateAllEnemies(float dt)
{
	GetEnemies().erase(
		std::remove_if(GetEnemies().begin(), GetEnemies().end(),
			[dt](auto& enemy) {
				enemy->Update(dt);
				return enemy->GetState() == Enemy::State::Dead;
			}),
		GetEnemies().end()
				);
}

void EnemySpawner::DrawEnemies(sf::RenderTarget& target)
{
	for(const auto& enemy: GetEnemies())
	{
		target.draw(*enemy);
	}
}

void EnemySpawner::SpawnEnemy()
{
	GetEnemies().emplace_back(spawnBehavior.prototype->Clone());
}