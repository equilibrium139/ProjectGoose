#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

class Enemy
{
public:
	enum class State
	{
		Moving,
		Attacking,
		Dying,
		Dead
	};
	virtual std::unique_ptr<Enemy> clone() = 0;
	virtual sf::FloatRect GetBounds() const = 0;
	virtual void Update(float dt) = 0;
	virtual void TakeDamage()
	{
		if (--hitPoints <= 0)
		{
			state = State::Dying;
		}
	}
	State GetState() { return state; }
	virtual ~Enemy() = default;
protected:
	State state = State::Moving;
	int hitPoints;
};

