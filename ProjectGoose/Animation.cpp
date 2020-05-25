#include "Animation.h"

Animation::Animation(const sf::Texture& sheet, int nFrames, int nRows, int nColumns, float framesPerSecond)
	:sheet(sheet), nFrames(nFrames), nRows(nRows), nColumns(nColumns), width(sheet.getSize().x / nColumns), 
	 height(sheet.getSize().y / nRows), frameDuration(1.0f / framesPerSecond)
{
	sprite.setTexture(sheet);
	sprite.setTextureRect(sf::IntRect(0, 0, width, height));
	setOrigin(width / 2.0f, height / 2.0f);
	// move(width / 2.0f, height / 2.0f);
}

void Animation::Update(float dt)
{
	frameDurationSoFar += dt;
	if (frameDurationSoFar > frameDuration)
	{
		GoNextFrame();
	}
}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite, states);
}

void Animation::GoNextFrame()
{
	currentFrame++;
	currentFrame %= nFrames;
	int row = currentFrame / nColumns;
	int column = currentFrame % nColumns;
	sprite.setTextureRect(sf::IntRect(column * width, row * height, width, height));
	frameDurationSoFar = 0.0f;
}
