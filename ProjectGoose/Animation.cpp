#include "Animation.h"

Animation::Animation(sf::Sprite& sprite, const SpriteSheet& spriteSheet, float framesPerSecond, bool loop, bool flip)
	:sprite(sprite), spriteSheet(spriteSheet), width(spriteSheet.sheet.getSize().x / spriteSheet.columns), 
	height(spriteSheet.sheet.getSize().y / spriteSheet.rows), frameDuration(1.0f / framesPerSecond), loop(loop), flip(flip)
{
	sprite.setTexture(spriteSheet.sheet);
	if (!flip)
	{
		sprite.setTextureRect(sf::IntRect(0, 0, width, height));
	}
	else
	{
		sprite.setTextureRect(sf::IntRect(width, 0, -width, height));
	}
}

void Animation::Update(float dt)
{
	frameDurationSoFar += dt;
	if (frameDurationSoFar > frameDuration)
	{
		sprite.setTexture(spriteSheet.sheet);
		GoNextFrame();
		frameDurationSoFar = 0.0f;
	}
}

bool Animation::Done(bool resetIfDone)
{
	bool done = !loop && currentFrame == spriteSheet.nFrames - 1;
	if (done && resetIfDone) { currentFrame = 0; }
	return done;
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
	if (!flip)
	{
		sprite.setTextureRect(sf::IntRect(column * width, row * height, width, height));
	}
	else
	{
		sprite.setTextureRect(sf::IntRect(column * width + width, row * height, -width, height));
	}
}
