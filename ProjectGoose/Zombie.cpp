#include "Zombie.h"

#include <iostream>

const SpriteSheet Zombie::maleWalk = SpriteSheet(ResourceHolder::GetTexture("Assets/Textures/maleZombieWalk.png"), 10, 3, 4);
const SpriteSheet Zombie::maleDeath = SpriteSheet(ResourceHolder::GetTexture("Assets/Textures/maleZombieDeath.png"), 12, 1, 12);
const SpriteSheet Zombie::femaleWalk = SpriteSheet(ResourceHolder::GetTexture("Assets/Textures/femaleZombieWalk.png"), 10, 1, 10);
const SpriteSheet Zombie::femaleDeath = SpriteSheet(ResourceHolder::GetTexture("Assets/Textures/femaleZombieDeath.png"), 12, 1, 12);

Zombie::Zombie(sf::Vector2f spawnPosition, ResourceHolder& resourceHolder, const sf::RenderWindow& wnd)
	: walk(male ? maleWalk : femaleWalk, 10.0f), death(male ? maleDeath : femaleDeath, 10.0f, false)
	/*maleWalk(resourceHolder.GetTexture("Assets/Textures/maleZombieAttack.png"), 8, 2, 4, 10),
     maleDeath(resourceHolder.GetTexture("Assets/Textures/maleZombieDeath.png"), 12, 1, 12, 10, false)*/
{
	transform.setScale(-0.15f, 0.15f); // mirror and scale down
	// auto bounds = maleWalk.GetBounds();
	transform.setPosition(spawnPosition);

}

void Zombie::Update(float dt)
{
	switch (state)
	{
	case State::Moving:
		transform.move(sf::Vector2f(-1.0f, 0.0f) * speed * dt);
		walk.Update(dt);
		break;
	case State::Dying:
		death.Update(dt);
		if (death.Done())
		{
			state = State::Dead;
		}
		break;
	}
}

void Zombie::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= transform.getTransform();
	auto bounds = walk.GetBounds();
	switch (state)
	{
	case State::Moving:
		target.draw(walk, states);
		break;
	case State::Dying:
		target.draw(death, states);
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