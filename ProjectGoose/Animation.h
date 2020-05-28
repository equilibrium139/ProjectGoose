#pragma once

#include <SFML/Graphics.hpp>

class Animation : public sf::Drawable
{
public:
	Animation(const sf::Texture& sheet, int nFrames, int nRows, int nColumns, float framesPerSecond = 6.0f, bool loop = true);
	void Update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::FloatRect GetBounds() const { return sprite.getLocalBounds(); }
	bool Done() { return !loop && currentFrame == nFrames - 1; }
private:
	void GoNextFrame();
private:
	const sf::Texture& sheet;
	sf::Sprite sprite;
	const int nFrames;
	const int nColumns;
	const int nRows;
	const int width;
	const int height;
	float frameDuration;
	float frameDurationSoFar = 0.0f;
	int currentFrame = 0;
	bool loop;
};