#include "Shooter.h"
#include <iostream>

Shooter::Shooter(const sf::RenderWindow& wnd, float cooldown)
	:screenBottom(wnd.getView().getSize().y), cd(cooldown), timeSinceLastShot(std::numeric_limits<float>::max())
{
}

void Shooter::AttemptShot(sf::Vector2f position)
{
	if (timeSinceLastShot > cd)
	{
		poops.emplace_back(position);
		timeSinceLastShot = 0.0f;
	}
}

void Shooter::Update(float dt)
{
	timeSinceLastShot += dt;
	poops.erase(
		std::remove_if(poops.begin(), poops.end(),
			[dt, this](Poop& poop) {
				poop.Update(dt);
				return poop.circle.getGlobalBounds().top > screenBottom
					|| poop.collided;
			}),
		poops.end()
	);
}

void Shooter::DrawPoops(sf::RenderTarget& target) const
{
	for (const auto& poop : poops)
	{
		target.draw(poop);
	}
}
