#pragma once

#include <random>
#include <variant>

#include <SFML/Graphics.hpp>

#include "Animation.h"
#include "ResourceHolder.h"
#include "Enemy.h"

class Zombie : public Enemy
{
public:
	Zombie(const sf::Vector2f& playerPosition, sf::Vector2f position = sf::Vector2f(0.0f, 0.0f), float scale = 0.15f, float speed = 100.0f, int hitPoints = 1, float attackCooldown = 5.0f);
	void Update(float dt) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::FloatRect GetBounds() const override { return sprite.getGlobalBounds(); }
	std::unique_ptr<Enemy> Clone() const override { return std::make_unique<Zombie>(playerPosition, sprite.getPosition(), sprite.getScale().x, speed, GetHitpoints()); }
private:
	static bool CoinFlip()
	{
		static std::random_device rd;
		static std::mt19937 rng(rd());
		static std::uniform_int_distribution<int> flip(0, 1);
		return flip(rng) == 0;
	}
	void LookAtPlayer(Animation& current);
private:
	bool male = CoinFlip();
	sf::Sprite sprite;
	Animation walk;
	Animation death;
	Animation attack;
	float speed;
	float attackCooldown;
	float timeSinceLastAttacked = 0.0f;
	const sf::Vector2f& playerPosition;
private:
	const static SpriteSheet& maleWalk();
	const static SpriteSheet& maleDeath();
	const static SpriteSheet& maleAttack();
	const static SpriteSheet& femaleWalk();
	const static SpriteSheet& femaleDeath();
	const static SpriteSheet& femaleAttack();

};