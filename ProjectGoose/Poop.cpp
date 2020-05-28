#include "Poop.h"

const sf::Color Poop::color = sf::Color(122, 89, 1);

Poop::Poop(sf::Vector2f position)
{
	auto circleCenter = circle.getRadius() / 2.0f;
	circle.setOrigin(circleCenter, circleCenter);
	circle.setPosition(position);
	circle.setFillColor(color);
}

void Poop::Update(float dt)
{
	circle.move(sf::Vector2f(0.0f, 1.0f) * speed * dt);
}