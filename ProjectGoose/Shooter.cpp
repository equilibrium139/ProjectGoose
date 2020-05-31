#include <iostream>

#include "Shooter.h"
#include "ResourceHolder.h"

Shooter::Shooter(const sf::RenderWindow& wnd, float cooldown)
	:screenBottom(wnd.getView().getSize().y), cd(cooldown), timeSinceLastShot(std::numeric_limits<float>::max()),
	splatterSoundBuffer(ResourceHolder::GetSoundBuffer("Assets/Sounds/wet-splat.wav"))
{
	splatterSound.setBuffer(splatterSoundBuffer);
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
				if (poop.collided)
				{
					splatterSound.play();
					return true;
				}
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
