#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

class Enemy : public sf::Drawable
{
public:
	enum class State
	{
		Moving,
		Attacking,
		Dying,
		Dead
	};
	virtual std::unique_ptr<Enemy> Clone() const = 0;
	virtual sf::FloatRect GetBounds() const = 0;
	virtual void Update(float dt) = 0;
	virtual void TakeDamage()
	{
		if (--hitPoints <= 0)
		{
			state = State::Dying;
		}
	}
	virtual void SetPosition(sf::Vector2f newPos) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
	State GetState() { return state; }
	bool IsDead() const { return hitPoints < 0; }
	int GetHitpoints() const { return hitPoints; }
	virtual ~Enemy() = default;
protected:
	Enemy(int hp)
		:hitPoints(hp) {}
	State state = State::Moving;
private:
	int hitPoints;
};

