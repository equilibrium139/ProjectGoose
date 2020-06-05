#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(std::unique_ptr<Enemy>&& proto, float spawnInterval, float spawnStartTime)
	:prototype(std::move(proto)), spawnInterval(spawnInterval), 
	timeSinceLastSpawnedEnemy(spawnInterval - spawnStartTime)
{
}

void EnemySpawner::Update(float dt)
{
	timeSinceLastSpawnedEnemy += dt;
	if (timeSinceLastSpawnedEnemy >= spawnInterval)
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
	GetEnemies().emplace_back(prototype->Clone());
}