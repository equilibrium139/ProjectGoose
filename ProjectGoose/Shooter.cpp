#include "Shooter.h"
#include <iostream>

const sf::Color Poop::color = sf::Color(122, 89, 1);

Shooter::Shooter(const sf::RenderWindow& wnd, float cooldown)
	:screenBottom(wnd.getView().getSize().y), cd(cooldown), timeSinceLastShot(std::numeric_limits<float>::max())
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
	poops.erase(
		std::remove_if(poops.begin(), poops.end(),
			[dt, this](Poop& poop) {
				poop.Update(dt);
				std::cout << poops.size() << '\n';
				return poop.circle.getGlobalBounds().top > screenBottom;
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
