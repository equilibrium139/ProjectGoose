#include "ZombieSpawner.h"
#include <iostream>

ZombieSpawner::ZombieSpawner(const sf::RenderWindow& window, sf::Vector2f spawnPos )
	:spawnPosition(spawnPos), timeSinceLastSpawned(std::numeric_limits<float>::max()),
	resourceHolder(resourceHolder), window(window)
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
				if (zombie->GetState() == Zombie::State::Dead)
				{
					std::cout << "Break";
				}
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

void ZombieSpawner::SpawnZombie()
{
	zombies.emplace_back(std::make_unique<Zombie>(spawnPosition, window));
}
