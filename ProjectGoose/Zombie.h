#pragma once

#include <random>
#include <variant>

#include <SFML/Graphics.hpp>

#include "Animation.h"
#include "ResourceHolder.h"

class Zombie : public sf::Drawable
{
public:
	Zombie(const sf::Vector2f& playerPosition, sf::Vector2f position, float scale = 0.15f, float speed = 100.0f, int hitPoints = 1);
	void Update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void TakeDamage();
	enum class State
	{
		Moving,
		Attacking,
		Dying,
		Dead
	};
	State GetState() const { return state; }
	sf::FloatRect GetBounds() const { return transform.getTransform().transformRect(walk.GetBounds()); }
private:
	bool CoinFlip() const
	{
		static std::random_device rd;
		static std::mt19937 rng(rd());
		static std::uniform_int_distribution<int> flip(0, 1);
		return flip(rng) == 0;
	}
private:
	bool male = CoinFlip();
	Animation walk;
	Animation death;
	Animation attack;
	const static SpriteSheet maleWalk;
	const static SpriteSheet maleDeath;
	const static SpriteSheet maleAttack;
	const static SpriteSheet femaleWalk;
	const static SpriteSheet femaleDeath;
	const static SpriteSheet femaleAttack;
	sf::Transformable transform;
	float scale;
	float speed;
	State state = State::Moving;
	int hitPoints;
	const float attackCooldown = 2.0f;
	float timeSinceLastAttacked = 0.0f;
	const sf::Vector2f& playerPosition;
};