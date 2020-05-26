#pragma once

#include <SFML/Graphics.hpp>

#include "Animation.h"
#include "ResourceHolder.h"

class Zombie : public sf::Drawable
{
public:
	Zombie(sf::Vector2f spawnPosition, ResourceHolder& resourceHolder, const sf::RenderWindow& window);
	void Update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void TakeDamage() const;
	enum class State
	{
		Walking,
		Attacking,
		Dying,
		Dead
	};
	State GetState() const { return state; }
	sf::FloatRect GetBounds() const { return maleWalk.GetBounds(); }
private:
	sf::Texture& maleWalkSheet;
	Animation maleWalk;
	//float animationChangeTime = 1.0f / 6.0f; // 6 frames per second
	//float timeSinceLastAnimationChange = 0.0f;
	//int currentFrame = 0;
	//const int nFrames = 10;
	//const int nRows = 3;
	//const int nColumns = 4;
	float speed = 100.0f;
	mutable State state = State::Walking;
	mutable int hitPoints = 3;
};