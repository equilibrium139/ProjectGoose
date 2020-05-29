#include "ZombieProjectile.h"
#include "ResourceHolder.h"
#include "VectorUtilities.h"

const sf::Texture& ZombieProjectile::rock = ResourceHolder::GetTexture("Assets/Textures/rock.png");
const float ZombieProjectile::scale = 0.05f;
std::vector<std::unique_ptr<ZombieProjectile>> ZombieProjectile::projectiles;

ZombieProjectile::ZombieProjectile(sf::Vector2f spawnLocation, sf::Vector2f targetLocation)
	:direction(targetLocation - spawnLocation)
{
	Normalize(direction);
	sprite.setTexture(rock);
	sprite.setScale(scale, scale);
	sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
	sprite.setPosition(spawnLocation);
}

void ZombieProjectile::Update(float dt)
{
	sprite.move(direction * speed * dt);
}

void ZombieProjectile::UpdateAll(float dt)
{
	for (auto& projectile : projectiles)
	{
		projectile->Update(dt);
	}
}

void ZombieProjectile::DrawAll(sf::RenderTarget& target)
{
	for (auto& projectile : projectiles)
	{
		target.draw(*projectile);
	}
}

void ZombieProjectile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

void ZombieProjectile::Spawn(sf::Vector2f spawnLocation, sf::Vector2f targetLocation)
{
	projectiles.emplace_back(std::make_unique<ZombieProjectile>(spawnLocation, targetLocation));
}