#pragma once

#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

struct ZombieProjectile : public sf::Drawable
{
	ZombieProjectile(sf::Vector2f spawnLocation, sf::Vector2f targetLocation);
	void Update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	static const sf::Texture& rock;
	static const float scale;
	static std::vector<std::unique_ptr<ZombieProjectile>> projectiles;
	static void Spawn(sf::Vector2f spawnLocation, sf::Vector2f targetLocation);
	static void UpdateAll(float dt);
	static void DrawAll(sf::RenderTarget& target);
	sf::Vector2f direction;
	sf::Sprite sprite;
	float speed = 300.0f;
};