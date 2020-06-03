#pragma once

#include <random>
#include <variant>

#include <SFML/Graphics.hpp>

#include "Animation.h"
#include "ResourceHolder.h"
#include "Enemy.h"

class Zombie : public sf::Drawable, public Enemy
{
public:
	Zombie(const sf::Vector2f& playerPosition, sf::Vector2f position, float scale = 0.15f, float speed = 100.0f, int hitPoints = 1);
	void Update(float dt) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::FloatRect GetBounds() const override { return sprite.getGlobalBounds(); }
	std::unique_ptr<Enemy> Clone() const override { return std::make_unique<Zombie>(playerPosition, sprite.getPosition(), sprite.getScale().x, speed, hitPoints); }
private:
	bool CoinFlip() const
	{
		static std::random_device rd;
		static std::mt19937 rng(rd());
		static std::uniform_int_distribution<int> flip(0, 1);
		return flip(rng) == 0;
	}
	void LookAtPlayer(Animation& current);
private:
	//TODO change to static functions
	const static SpriteSheet maleWalk;
	const static SpriteSheet maleDeath;
	const static SpriteSheet maleAttack;
	const static SpriteSheet femaleWalk;
	const static SpriteSheet femaleDeath;
	const static SpriteSheet femaleAttack;

	bool male = CoinFlip();
	sf::Sprite sprite;
	Animation walk;
	Animation death;
	Animation attack;
	float speed;
	const float attackCooldown = 2.0f;
	float timeSinceLastAttacked = 0.0f;
	const sf::Vector2f& playerPosition;
};