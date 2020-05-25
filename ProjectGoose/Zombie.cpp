#include "Zombie.h"

#include <iostream>

Zombie::Zombie(ResourceHolder& resourceHolder, sf::RenderWindow& wnd)
	:maleWalkSheet(resourceHolder.GetTexture("Assets/Textures/maleZombieWalk.png"))
{
	sprite.setTexture(maleWalkSheet);
	sprite.setTextureRect(sf::IntRect(0, 0, maleWalkSheet.getSize().x / nColumns, maleWalkSheet.getSize().y / nRows));
	sprite.setScale(-0.15f, 0.15f);
	auto bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
	std::cout << wnd.getView().getSize().x << '\n';
	sprite.setPosition(wnd.getSize().x, wnd.getView().getSize().y - 200.0f);
}

void Zombie::Update(float dt)
{
	sprite.move(sf::Vector2f(-1.0f, 0.0f) * speed * dt);
}

void Zombie::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	auto bounds = sprite.getGlobalBounds();
	sf::RectangleShape rect({ bounds.width, bounds.height });
	rect.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
	rect.setPosition(sprite.getPosition());
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineColor(sf::Color::Green);
	rect.setOutlineThickness(5.0f);
	target.draw(sprite, states);
	target.draw(rect, states);
}
