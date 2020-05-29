#pragma once

#include "Poop.h"
#include <SFML/Graphics.hpp>

class Shooter
{
public:
	explicit Shooter(const sf::RenderWindow& wnd, float cooldown = 1.0f);
	void AttemptShot(sf::Vector2f position);
	void Update(float dt);
	void DrawPoops(sf::RenderTarget& target) const;
	std::vector<Poop>& GetPoops() { return poops; }
private:
	float screenBottom;
	float cd;
	float timeSinceLastShot;
	std::vector<Poop> poops;
};