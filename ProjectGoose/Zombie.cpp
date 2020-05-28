#include "Zombie.h"

#include <iostream>

Zombie::Zombie(sf::Vector2f spawnPosition, ResourceHolder& resourceHolder, const sf::RenderWindow& wnd)
	:maleWalk(resourceHolder.GetTexture("Assets/Textures/maleZombieAttack.png"), 8, 2, 4, 10),
     maleDeath(resourceHolder.GetTexture("Assets/Textures/maleZombieDeath.png"), 12, 1, 12, 10, false)
{
	transform.setScale(-0.15f, 0.15f); // mirror and scale down
	auto bounds = maleWalk.GetBounds();
	transform.setPosition(spawnPosition);

}

void Zombie::Update(float dt)
{
	switch (state)
	{
	case State::Walking:
		transform.move(sf::Vector2f(-1.0f, 0.0f) * speed * dt);
		maleWalk.Update(dt);
		break;
	case State::Dying:
		maleDeath.Update(dt);
		if (maleDeath.Done())
		{
			state = State::Dead;
		}
		break;
	}
}

void Zombie::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= transform.getTransform();
	auto bounds = maleWalk.GetBounds();
	switch (state)
	{
	case State::Walking:
		target.draw(maleWalk, states);
		break;
	case State::Dying:
		target.draw(maleDeath, states);
		break;
	}
	// target.draw(rect, states);
}

void Zombie::TakeDamage() const
{
	std::cout << "Ouch\n";
	if (--hitPoints <= 0)
	{
		state = State::Dying;
	}
}