#include "EnemySpawner.h"
#include <iostream>

EnemySpawner::EnemySpawner(const EnemySpawnBehavior& minionSpawnBehavior, const EnemySpawnBehavior& giantSpawnBehavior)
	:minionSpawnBehavior(minionSpawnBehavior), giantSpawnBehavior(giantSpawnBehavior),
	timeSinceLastSpawnedMinion(this->minionSpawnBehavior.spawnInterval - this->minionSpawnBehavior.spawnStartTime),
	timeSinceLastSpawnedGiant(this->giantSpawnBehavior.spawnInterval - this->giantSpawnBehavior.spawnStartTime)
{
}

void EnemySpawner::Update(float dt)
{
	timeSinceLastSpawnedMinion += dt;
	timeSinceLastSpawnedGiant += dt;
	if (timeSinceLastSpawnedMinion >= minionSpawnBehavior.spawnInterval)
	{
		SpawnEnemy(minionSpawnBehavior);
		timeSinceLastSpawnedMinion = 0.0f;
	}
	if (timeSinceLastSpawnedGiant >= giantSpawnBehavior.spawnInterval)
	{
		SpawnEnemy(giantSpawnBehavior);
		timeSinceLastSpawnedGiant = 0.0f;
	}
	enemies.erase(
		std::remove_if(enemies.begin(), enemies.end(),
			[dt](auto& enemy) {
				enemy->Update(dt);
				return enemy->GetState() == Enemy::State::Dead;
			}),
		enemies.end()
	);
}

void EnemySpawner::DrawEnemies(sf::RenderTarget& target)
{
	for(const auto& enemy: enemies)
	{
		target.draw(*enemy);
	}
}

void EnemySpawner::SpawnEnemy(const EnemySpawnBehavior& spawnBehavior)
{
	enemies.emplace_back(spawnBehavior.prototype->Clone());
}