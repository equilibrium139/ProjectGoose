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
	: Enemy(hitPoints), walk(sprite, male ? maleWalk : femaleWalk, 10.0f, true, true), death(sprite, male ? maleDeath : femaleDeath, 10.0f, false, true),
	  attack(sprite, male ? maleAttack : femaleAttack, 10.0f, false, true), playerPosition(playerPosition), speed(speed)
{
	sprite.setScale(scale, scale);
	auto bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
	sprite.setPosition(position);
}

void Zombie::Update(float dt)
{
	if (timeSinceLastAttacked > attackCooldown && state != State::Dying && state != State::Dead)
	{
		state = State::Attacking;
		
		LookAtPlayer(attack);
		ZombieProjectile::Spawn(sprite.getPosition()/* + sf::Vector2f(sprite.getScale().x * 260.0f, sprite.getScale().y * 330.0f)*/, playerPosition);
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
		sprite.move(sf::Vector2f(-1.0f, 0.0f) * speed * dt);
		walk.Update(dt);
		timeSinceLastAttacked += dt;
		break;
	case State::Attacking:
		attack.Update(dt);
		
		if (attack.Done(true))
		{
			state = State::Moving;
		}
		break;
	}

	if (GetBounds().left + GetBounds().width < 0)
	{
		state = State::Dead;
	}
}

void Zombie::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	/*auto bounds = sprite.getGlobalBounds();
	sf::RectangleShape rs({ bounds.width, bounds.height });
	rs.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
	rs.setPosition(sprite.getPosition());
	rs.setFillColor(sf::Color::Transparent);
	rs.setOutlineThickness(5.0f);
	rs.setOutlineColor(sf::Color::Green);*/
	target.draw(sprite, states);
	// target.draw(rs, states);
}

void Zombie::LookAtPlayer(Animation& current)
{
	if (playerPosition.x > sprite.getPosition().x)
	{
		current.SetFlip(false);
	}
	else
	{
		current.SetFlip(true);
	}
}