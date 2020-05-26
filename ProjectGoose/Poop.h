#pragma once

#include <SFML/Graphics.hpp>

struct Poop : public sf::Drawable
{
	Poop(sf::Vector2f position)
	{
		auto circleCenter = circle.getRadius() / 2.0f;
		circle.setOrigin(circleCenter, circleCenter);
		circle.setPosition(position);
		circle.setFillColor(color);
	}
	void Update(float dt)
	{
		circle.move(sf::Vector2f(0.0f, 1.0f) * speed * dt);
	}
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(circle, states);
	}
	sf::FloatRect GetBounds() const { return circle.getGlobalBounds(); }
	sf::CircleShape circle = sf::CircleShape(5.0f);
	static const sf::Color color;
	float speed = 300.0f;
};