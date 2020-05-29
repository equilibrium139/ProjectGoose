#include "ZombieSpawner.h"
#include "ZombieProjectile.h"
#include <iostream>

ZombieSpawner::ZombieSpawner(const sf::RenderWindow& window, const sf::Vector2f& playerPosition, sf::Vector2f spawnPos)
	:spawnPosition(spawnPos), timeSinceLastSpawned(std::numeric_limits<float>::max()),
	 window(window), playerPosition(playerPosition)
{
}

void ZombieSpawner::Update(float dt)
{
	timeSinceLastSpawned += dt;
	if (timeSinceLastSpawned > spawnInterval)
	{
		SpawnZombie();
		timeSinceLastSpawned = 0.0f;
	}

	zombies.erase(
		std::remove_if(zombies.begin(), zombies.end(),
			[dt](auto& zombie) {
				zombie->Update(dt);
				return zombie->GetState() == Zombie::State::Dead;
			}),
		zombies.end()
	);

	ZombieProjectile::UpdateAll(dt);
}

void ZombieSpawner::DrawZombies(sf::RenderTarget& target)
{
	for(const auto& zombie: zombies)
	{
		target.draw(*zombie);
	}

	ZombieProjectile::DrawAll(target);
}

void ZombieSpawner::SpawnZombie()
{
	zombies.emplace_back(std::make_unique<Zombie>(spawnPosition, window, playerPosition));
}
