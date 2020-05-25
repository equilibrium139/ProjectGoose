#pragma once

#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "ResourceHolder.h"

class Goose : public sf::Drawable
{
public:
	Goose(ResourceHolder& resourceHolder, const sf::RenderWindow& window);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void Update(float dt);
private:
	void ClampToWindow();
private:
	const sf::RenderWindow& window;
	sf::Texture& texture;
	/*sf::Sprite sprite;*/
	Animation animation;
	float scale = 0.1f;
	float speed = 100.0f;
	//float animationChangeTime = 1.0f / 6.0f; // 6 frames per second
	//float timeSinceLastAnimationChange = 0.0f;
	//int currentFrame = 0;
	//const int nFrames = 3;
};