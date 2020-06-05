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

// Update enemies and remove them from the list if dead or if they're off the window
void EnemySpawner::UpdateAllEnemies(float dt, const sf::RenderWindow& window)
{
	auto windowSize = window.getView().getSize();
	sf::FloatRect windowBounds(0.0f, 0.0f, windowSize.x, windowSize.y);

	GetEnemies().erase(
		std::remove_if(GetEnemies().begin(), GetEnemies().end(),
			[dt, &windowBounds](auto& enemy) {
				enemy->Update(dt);
				return enemy->GetState() == Enemy::State::Dead || 
					!windowBounds.intersects(enemy->GetBounds());
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