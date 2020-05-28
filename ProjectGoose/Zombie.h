#pragma once

#include <random>
#include <variant>

#include <SFML/Graphics.hpp>

#include "Animation.h"
#include "ResourceHolder.h"

class Zombie : public sf::Drawable
{
public:
	Zombie(sf::Vector2f spawnPosition, ResourceHolder& resourceHolder, const sf::RenderWindow& window);
	void Update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void TakeDamage() const;
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
	const static SpriteSheet maleWalk;
	const static SpriteSheet maleDeath;
	const static SpriteSheet femaleWalk;
	const static SpriteSheet femaleDeath;
	/*Animation maleWalk;
	Animation maleDeath;*/
	sf::Transformable transform;
	float speed = 100.0f;
	mutable State state = State::Moving;
	mutable int hitPoints = 3;
};