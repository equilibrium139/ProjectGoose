#pragma once

#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"

class Zombie : public sf::Drawable
{
public:
	Zombie(ResourceHolder& resourceHolder, sf::RenderWindow& window);
	void Update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	sf::Texture& maleWalkSheet;
	sf::Sprite sprite;
	float animationChangeTime = 1.0f / 6.0f; // 6 frames per second
	float timeSinceLastAnimationChange = 0.0f;
	int currentFrame = 0;
	const int nFrames = 10;
	const int nRows = 3;
	const int nColumns = 4;
	float speed = 100.0f;
};