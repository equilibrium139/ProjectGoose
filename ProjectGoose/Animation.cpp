#include "Animation.h"

Animation::Animation(const sf::Texture& sheet, int nFrames, int nRows, int nColumns, float framesPerSecond, bool loop)
	:spriteSheet{ sheet, nFrames, nRows, nColumns }, width(sheet.getSize().x / nColumns),
	 height(sheet.getSize().y / nRows), frameDuration(1.0f / framesPerSecond), loop(loop)
{
	sprite.setTexture(spriteSheet.sheet);
	sprite.setTextureRect(sf::IntRect(0, 0, width, height));
}

Animation::Animation(const SpriteSheet& spriteSheet, float framesPerSecond, bool loop)
	:Animation(spriteSheet.sheet, spriteSheet.nFrames, spriteSheet.rows, spriteSheet.columns, framesPerSecond, loop)
{
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
	target.draw(sprite, states);
}

void Animation::GoNextFrame()
{
	currentFrame++;
	if (currentFrame == spriteSheet.nFrames && !loop)
	{
		--currentFrame;
		return;
	}
	currentFrame %= spriteSheet.nFrames;
	int row = currentFrame / spriteSheet.columns;
	int column = currentFrame % spriteSheet.columns;
	sprite.setTextureRect(sf::IntRect(column * width, row * height, width, height));
	frameDurationSoFar = 0.0f;
}
