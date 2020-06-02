#include <iostream>

#include "Zombie.h"
#include "ZombieProjectile.h"

const SpriteSheet Zombie::maleWalk = SpriteSheet(ResourceHolder::GetTexture("Assets/Textures/maleZombieWalk.png"), 10, 3, 4);
const SpriteSheet Zombie::maleDeath = SpriteSheet(ResourceHolder::GetTexture("Assets/Textures/maleZombieDeath.png"), 12, 1, 12);
const SpriteSheet Zombie::maleAttack = SpriteSheet(ResourceHolder::GetTexture("Assets/Textures/maleZombieAttack.png"), 8, 1, 8);
const SpriteSheet Zombie::femaleWalk = SpriteSheet(ResourceHolder::GetTexture("Assets/Textures/femaleZombieWalk.png"), 10, 1, 10);
const SpriteSheet Zombie::femaleDeath = SpriteSheet(ResourceHolder::GetTexture("Assets/Textures/femaleZombieDeath.png"), 12, 1, 12);
const SpriteSheet Zombie::femaleAttack = SpriteSheet(ResourceHolder::GetTexture("Assets/Textures/femaleZombieAttack.png"), 8, 1, 8);

Zombie::Zombie(const sf::Vector2f& playerPosition, sf::Vector2f position, float scale, float speed, int hitPoints)
	: walk(male ? maleWalk : femaleWalk, 10.0f), death(male ? maleDeath : femaleDeath, 10.0f, false),
	  attack(male ? maleAttack : femaleAttack, 10.0f, false), playerPosition(playerPosition), speed(speed), hitPoints(hitPoints)
	/*maleWalk(resourceHolder.GetTexture("Assets/Textures/maleZombieAttack.png"), 8, 2, 4, 10),
     maleDeath(resourceHolder.GetTexture("Assets/Textures/maleZombieDeath.png"), 12, 1, 12, 10, false)*/
{
	transform.setScale(-scale, scale); // mirror and scale down
	auto bounds = GetBounds();
	transform.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
	transform.setPosition(position);
}

void Zombie::Update(float dt)
{
	if (GetBounds().left + GetBounds().width < 0)
	{
		state = State::Dead;
	}
	//TODO refactor
	timeSinceLastAttacked += dt;
	if (timeSinceLastAttacked > attackCooldown && state != State::Dying && state != State::Dead)
	{
		state = State::Attacking;
		if (playerPosition.x > transform.getPosition().x)
		{
			transform.setScale(std::abs(transform.getScale().x), transform.getScale().y);
		}
		else
		{
			transform.setScale(-std::abs(transform.getScale().x), transform.getScale().y);
		}
		std::cout << transform.getScale().x << '\n';
		ZombieProjectile::Spawn(transform.getPosition() + sf::Vector2f(transform.getScale().x * 260.0f, transform.getScale().y * 330.0f), playerPosition);
		timeSinceLastAttacked = 0.0f;
	}
	switch (state)
	{
	case State::Dying:
		death.Update(dt);
		if (death.Done())
		{
			state = State::Dead;
		}
		break;
	case State::Moving:
		transform.move(sf::Vector2f(-1.0f, 0.0f) * speed * dt);
		walk.Update(dt);
		break;
	case State::Attacking:
		attack.Update(dt);
		
		if (attack.Done(true))
		{
			transform.setScale(-std::abs(transform.getScale().x), transform.getScale().y);
			state = State::Moving;
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
	case State::Attacking:
		target.draw(attack, states);
		break;
	}
	// target.draw(rect, states);
}

void Zombie::TakeDamage()
{
	std::cout << "Ouch\n";
	if (--hitPoints <= 0)
	{
		state = State::Dying;
	}
}