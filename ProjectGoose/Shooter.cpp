#include "Shooter.h"

Shooter::Shooter(float cooldown)
	:cd(cooldown), timeSinceLastShot(std::numeric_limits<float>::max())
{
}

void Shooter::AttemptShot(sf::Vector2f position)
{
	if (timeSinceLastShot > cd)
	{
		poops.emplace_back(std::move(position));
		timeSinceLastShot = 0.0f;
	}
}

void Shooter::Update(float dt)
{
	timeSinceLastShot += dt;
	for (auto& poop : poops)
	{
		poop.Update(dt);
	}
}

void Shooter::DrawPoops(sf::RenderTarget& target) const
{
	for (const auto& poop : poops)
	{
		target.draw(poop);
	}
}
