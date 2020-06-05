#include "ZombieBird.h"
#include "VectorUtilities.h"

#include <iostream>

ZombieBird::ZombieBird(const sf::Vector2f& playerPos, sf::Vector2f spawnPos, float scale, float speed, int hitpoints, bool targetPlayer)
	:Enemy(hitpoints), playerPos(playerPos), fly(sprite, sheet(), 6.0f, true, true), speed(speed), targetPlayer(targetPlayer)
{
	auto bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
	sprite.setScale(scale, scale);
	sprite.setPosition(spawnPos);
}

void ZombieBird::Update(float dt)
{
	sf::Vector2f direction;
	switch (state)
	{
	case State::Moving:
	{
		fly.Update(dt);
		// Only attack player if in front of him
		if (targetPlayer && sprite.getPosition().x > playerPos.x)
		{
			direction = playerPos - sprite.getPosition();
			Normalize(direction);
		}
		else
		{
			direction = sf::Vector2f(-1.0f, 0.0f);
			// sprite.move(sf::Vector2f(-1.0f, 0.0f) * speed * dt);
		}
		break;
	}
	case State::Dying:
		direction = sf::Vector2f(0.0f, 1.0f);
		sprite.setScale(sprite.getScale().x, -std::abs(sprite.getScale().y));
		speed += 1000.f * dt;
		break;
	}
	sprite.move(direction * speed * dt);
}

std::unique_ptr<Enemy> ZombieBird::Clone() const
{
	std::cout << "Cloning\n";
	return std::make_unique<ZombieBird>(playerPos, sprite.getPosition(), sprite.getScale().x, 
		speed, targetPlayer);
}
