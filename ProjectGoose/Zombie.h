#pragma once

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
		Walking,
		Attacking,
		Dying,
		Dead
	};
	State GetState() const { return state; }
	sf::FloatRect GetBounds() const { return transform.getTransform().transformRect(maleWalk.GetBounds()); }

	Zombie(const Zombie&) = default;
	Zombie& operator=(const Zombie&) { return *this; }
	Zombie(Zombie&&) = default;
	Zombie& operator=(Zombie&&) { return *this; }
private:
	Animation maleWalk;
	Animation maleDeath;
	sf::Transformable transform;
	float speed = 100.0f;
	mutable State state = State::Walking;
	mutable int hitPoints = 3;
};