#pragma once

#include <SFML/Graphics.hpp>

struct Poop : public sf::Drawable
{
	Poop(sf::Vector2f position);
	void Update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(circle, states);
	}
	sf::FloatRect GetBounds() const { return circle.getGlobalBounds(); }
	sf::CircleShape circle = sf::CircleShape(5.0f);
	static const sf::Color color;
	float speed = 300.0f;
	mutable bool collided = false;
};