#pragma once

#include <SFML/Graphics.hpp>

class Goose : public sf::Drawable
{
public:
	Goose(const sf::RenderWindow& window);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void Update(float dt);
private:
	void ClampToWindow();
private:
	const sf::RenderWindow& window;
	sf::Texture texture;
	sf::Sprite sprite;
	float scale = 0.1f;
	float speed = 100.0f;
	float animationChangeTime = 1.0f / 6.0f; // 6 frames per second
	float timeSinceLastAnimationChange = 0.0f;
	int currentFrame = 0;
	const int nFrames = 3;
};