#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Animation.h"
#include "ResourceHolder.h"
#include "Shooter.h"
#include "ZombieSpawner.h"
#include "SpriteSheet.h"

// Player will play as a Goose. Standard WASD movement, with Space to poop on zombies
// Movement is clamped to within the bounds of the window

class Goose : public sf::Drawable
{
public:
	// Goose(const sf::RenderWindow& window);
	Goose(const sf::RenderWindow& window, sf::Vector2f position = { 0.0f, 0.0f }, float scale = 0.1f, float speed = 150.0f, int hitPoints = 3);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void Update(float dt);
	void ProcessMovementInput(float dt);
	/*
		Detects if the goose is colliding with any zombies, or if any zombies got hit by poop
	*/
	void DetectCollisions(ZombieSpawner& zombieSpawner);
	sf::FloatRect GetBounds() const { return sprite.getGlobalBounds(); }
	const sf::Vector2f& GetPosition() const { return sprite.getPosition(); }
private:
	void ClampToWindow();
	void TakeDamage() { --hitPoints; std::cout << "Collided with zombie\n"; }
private:
	const static SpriteSheet& sheet()
	{
		static SpriteSheet flySheet = SpriteSheet(ResourceHolder::GetTexture("Assets/Textures/gooseSpritesheet.png"), 3, 3, 1);
		return flySheet;
	}
	const sf::RenderWindow& window;
	sf::Sprite sprite;
	Animation animation;
	Shooter shooter;
	float speed;
	int hitPoints;
};