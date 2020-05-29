#pragma once

#include <SFML/Graphics.hpp>

#include "SpriteSheet.h"

// Enables playing animations from spritesheets
class Animation : public sf::Drawable
{
public:
	Animation(const sf::Texture& sheet, int nFrames, int nRows, int nColumns, float framesPerSecond = 6.0f, bool loop = true);
	Animation(const SpriteSheet& spriteSheet, float framesPerSecond = 6.0f, bool loop = true);
	void Update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::FloatRect GetBounds() const { return sprite.getLocalBounds(); }
	bool Done() { return !loop && currentFrame == spriteSheet.nFrames - 1; }
	void Reset() { currentFrame = 0; }
private:
	void GoNextFrame();
private:
	SpriteSheet spriteSheet;
	sf::Sprite sprite;
	const int width;
	const int height;
	float frameDuration;
	float frameDurationSoFar = 0.0f;
	int currentFrame = 0;
	bool loop;
};