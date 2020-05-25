#include "Zombie.h"

#include <iostream>

Zombie::Zombie(ResourceHolder& resourceHolder, sf::RenderWindow& wnd)
	:maleWalkSheet(resourceHolder.GetTexture("Assets/Textures/maleZombieAttack.png")), 
	 maleWalk(maleWalkSheet, 8, 2, 4, 10)
{
	maleWalk.scale(-0.15f, 0.15f);
	maleWalk.setPosition(wnd.getSize().x, wnd.getView().getSize().y - 200.0f);
}

void Zombie::Update(float dt)
{
	switch (state)
	{
	case State::Walking:
		maleWalk.move(sf::Vector2f(-1.0f, 0.0f) * speed * dt);
		maleWalk.Update(dt);
		break;
	}
}

void Zombie::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	auto bounds = maleWalk.GetBounds();
	/*sf::RectangleShape rect({ bounds.width, bounds.height });
	rect.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
	rect.setPosition(sprite.getPosition());
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineColor(sf::Color::Green);
	rect.setOutlineThickness(5.0f);*/
	target.draw(maleWalk, states);
	// target.draw(rect, states);
}
