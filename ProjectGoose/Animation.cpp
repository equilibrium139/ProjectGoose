#include "Animation.h"
#include <iostream>
//Animation::Animation(sf::Sprite& sprite, const sf::Texture& sheet, int nFrames, int nRows, int nColumns, float framesPerSecond, bool loop, bool flip)
//	:sprite_(sprite), spriteSheet_{ sheet, nFrames, nRows, nColumns }, width(sheet.getSize().x / nColumns),
//	height(sheet.getSize().y / nRows), frameDuration(1.0f / framesPerSecond), loop(loop), flip(flip)
//{
//	// sprite.setTexture(spriteSheet.sheet);
//	if (!flip)
//	{
//		sprite_.setTextureRect(sf::IntRect(0, 0, width, height));
//	}
//	else
//	{
//		sprite_.setTextureRect(sf::IntRect(width, 0, -width, height));
//	}
//}

Animation::Animation(sf::Sprite& sprite, const SpriteSheet& spriteSheet, float framesPerSecond, bool loop, bool flip)
	/*Animation(sprite, spriteSheet.sheet, spriteSheet.nFrames, spriteSheet.rows, spriteSheet.columns, framesPerSecond, loop, flip)*/
	:sprite_(sprite), spriteSheet_(spriteSheet), width(spriteSheet_.sheet.getSize().x / spriteSheet.columns), 
	height(spriteSheet_.sheet.getSize().y / spriteSheet_.rows), frameDuration(1.0f / framesPerSecond), loop(loop), flip(flip)
{
	sprite_.setTexture(spriteSheet_.sheet);
	if (!flip)
	{
		sprite_.setTextureRect(sf::IntRect(0, 0, width, height));
	}
	else
	{
		sprite_.setTextureRect(sf::IntRect(width, 0, -width, height));
	}
}

void Animation::Update(float dt)
{
	frameDurationSoFar += dt;
	if (frameDurationSoFar > frameDuration)
	{
		sprite_.setTexture(spriteSheet_.sheet);
		GoNextFrame();
		frameDurationSoFar = 0.0f;
	}
}

void Animation::GoNextFrame()
{
	currentFrame++;
	if (currentFrame == spriteSheet_.nFrames && !loop)
	{
		--currentFrame;
		return;
	}
	currentFrame %= spriteSheet_.nFrames;
	int row = currentFrame / spriteSheet_.columns;
	int column = currentFrame % spriteSheet_.columns;
	if (!flip)
	{
		sprite_.setTextureRect(sf::IntRect(column * width, row * height, width, height));
	}
	else
	{
		sprite_.setTextureRect(sf::IntRect(column * width + width, row * height, -width, height));
	}
}
