#pragma once

#include <SFML/Graphics.hpp>

#include "SpriteSheet.h"

// Enables playing animations from spritesheets
class Animation
{
public:
	Animation(sf::Sprite& sprite, const SpriteSheet& spriteSheet, float framesPerSecond = 6.0f, bool loop = true, bool flip = false);
	void Update(float dt);
	bool Done(bool resetIfDone = false);
	void Reset() { currentFrame = 0; }
	void SetFlip(bool f) { flip = f; }
	bool IsFlipped() const { return flip; }
	sf::FloatRect GetBounds() const { return sprite.getLocalBounds(); }
private:
	void GoNextFrame();
private:
	const SpriteSheet& spriteSheet;
	sf::Sprite& sprite;
	const int width;
	const int height;
	float frameDuration;
	float frameDurationSoFar = 0.0f;
	int currentFrame = 0;
	bool loop;
	bool flip;
};