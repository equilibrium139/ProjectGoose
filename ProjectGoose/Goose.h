#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Animation.h"
#include "ResourceHolder.h"
#include "Shooter.h"
#include "ZombieSpawner.h"

class Goose : public sf::Drawable
{
public:
	Goose(const sf::RenderWindow& window);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void Update(float dt);
	void DetectCollisions(ZombieSpawner& zombieSpawner);
	sf::FloatRect GetBounds() const { return transform.getTransform().transformRect(animation.GetBounds()); }
	const sf::Vector2f& GetPosition() const { return transform.getPosition(); }
private:
	void ClampToWindow();
	void TakeDamage() { --hitPoints; std::cout << "Collided with zombie\n"; }
private:
	const sf::RenderWindow& window;
	sf::Transformable transform;
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