#pragma once

#include "Poop.h"
#include <SFML/Graphics.hpp>

class Shooter
{
public:
	explicit Shooter(float cooldown = 1.0f);
	void AttemptShot(sf::Vector2f position);
	void Update(float dt);
	void DrawPoops(sf::RenderTarget& target) const;
private:
	float cd;
	float timeSinceLastShot;
	std::vector<Poop> poops;
};