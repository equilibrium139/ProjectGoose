#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

#include "Animation.h"
#include "ResourceHolder.h"
#include "Shooter.h"
#include "ZombieSpawner.h"

class Goose : public sf::Drawable
{
public:
	Goose(ResourceHolder& resourceHolder, const sf::RenderWindow& window);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void Update(float dt);
	void DetectCollisions(ZombieSpawner& zombieSpawner);
	sf::FloatRect GetBounds() const { return animation.GetBounds(); }
private:
	void ClampToWindow();
	void TakeDamage() { --hitPoints; std::cout << "Collided with zombie\n"; }
private:
	const sf::RenderWindow& window;
	sf::Texture& texture;
	/*sf::Sprite sprite;*/
	Animation animation;
	float scale = 0.1f;
	float speed = 150.0f;
	Shooter shooter;
	int hitPoints = 3;
	//float animationChangeTime = 1.0f / 6.0f; // 6 frames per second
	//float timeSinceLastAnimationChange = 0.0f;
	//int currentFrame = 0;
	//const int nFrames = 3;
};