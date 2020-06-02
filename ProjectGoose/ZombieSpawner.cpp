#include "ZombieSpawner.h"
#include <iostream>

ZombieSpawner::ZombieSpawner(const sf::Vector2f& playerPosition, const ZombieSpawnBehavior& minionSpawnBehavior, const ZombieSpawnBehavior& giantSpawnBehavior)
	:playerPosition(playerPosition), minionSpawnBehavior(minionSpawnBehavior), giantSpawnBehavior(giantSpawnBehavior),
	timeSinceLastSpawnedMinion(this->minionSpawnBehavior.spawnInterval - this->minionSpawnBehavior.minionSpawnStartTime),
	timeSinceLastSpawnedGiant(this->giantSpawnBehavior.spawnInterval - this->giantSpawnBehavior.minionSpawnStartTime)
{
}

void ZombieSpawner::Update(float dt)
{
	timeSinceLastSpawnedMinion += dt;
	timeSinceLastSpawnedGiant += dt;
	if (timeSinceLastSpawnedMinion >= minionSpawnBehavior.spawnInterval)
	{
		SpawnZombie(minionSpawnBehavior);
		timeSinceLastSpawnedMinion = 0.0f;
	}
	if (timeSinceLastSpawnedGiant >= giantSpawnBehavior.spawnInterval)
	{
		SpawnZombie(giantSpawnBehavior);
		timeSinceLastSpawnedGiant = 0.0f;
	}
	zombies.erase(
		std::remove_if(zombies.begin(), zombies.end(),
			[dt](auto& zombie) {
				zombie->Update(dt);
				return zombie->GetState() == Zombie::State::Dead;
			}),
		zombies.end()
	);
}

void ZombieSpawner::DrawZombies(sf::RenderTarget& target)
{
	for(const auto& zombie: zombies)
	{
		target.draw(*zombie);
	}
}

void ZombieSpawner::SpawnZombie(const ZombieSpawnBehavior& spawnBehavior)
{
	zombies.emplace_back(std::make_unique<Zombie>(playerPosition, spawnBehavior.spawnPos, spawnBehavior.scale, spawnBehavior.speed,
		spawnBehavior.hitpoints));
}