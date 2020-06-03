#pragma once

#include <SFML/Graphics.hpp>

#include "SpriteSheet.h"

// Enables playing animations from spritesheets
class Animation
{
public:
	// Animation(sf::Sprite& sprite, const sf::Texture& sheet, int nFrames, int nRows, int nColumns, float framesPerSecond = 6.0f, bool loop = true, bool flip = false);
	Animation(sf::Sprite& sprite, const SpriteSheet& spriteSheet, float framesPerSecond = 6.0f, bool loop = true, bool flip = false);
	void Update(float dt);
	// sf::FloatRect GetBounds() const { return sprite.getLocalBounds(); }
	bool Done(bool resetIfDone = false) { 
		bool done = !loop && currentFrame == spriteSheet_.nFrames - 1;
		if (done && resetIfDone) { currentFrame = 0; }
		return done;
	}
	void Reset() { currentFrame = 0; }
	void SetFlip(bool f) { flip = f; }
	bool IsFlipped() const { return flip; }
	const sf::Texture& GetTexture() const { return spriteSheet_.sheet; }
	sf::FloatRect GetBounds() const { return sprite_.getLocalBounds(); }
private:
	void GoNextFrame();
private:
	const SpriteSheet& spriteSheet_;
	sf::Sprite& sprite_;
	const int width;
	const int height;
	float frameDuration;
	float frameDurationSoFar = 0.0f;
	int currentFrame = 0;
	bool loop;
	bool flip;
};