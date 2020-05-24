#include "Goose.h"
#include "Vec2.h"

Goose::Goose(const sf::RenderWindow& in_window)
	:window(in_window)
{
	texture.loadFromFile("Assets/Textures/gooseSpritesheet.png");
	sprite.setTexture(texture);
	sprite.setTextureRect({ 0, currentFrame * (int)texture.getSize().y / 3, (int)texture.getSize().x, (int)texture.getSize().y / 3 });
	sprite.setScale(scale, scale);
	auto bounds = sprite.getLocalBounds();
	sprite.setOrigin({ bounds.width / 2.0f, bounds.height / 2.0f });
}

void Goose::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

void Goose::Update(float dt)
{
	timeSinceLastAnimationChange += dt;
	if (timeSinceLastAnimationChange >= animationChangeTime)
	{
		currentFrame++;
		currentFrame %= nFrames;
		sprite.setTextureRect({ 0, currentFrame * (int)texture.getSize().y / 3, (int)texture.getSize().x, (int)texture.getSize().y / 3 });
		timeSinceLastAnimationChange = 0.0f;
	}
	Vec2f moveVec;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		moveVec.y -= 1.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		moveVec.y += 1.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		moveVec.x -= 1.0f;
		sprite.setScale(-scale, scale);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		moveVec.x += 1.0f;
		sprite.setScale(scale, scale);
	}
	sprite.move(moveVec.Normalize() * speed * dt);
	ClampToWindow();
}

void Goose::ClampToWindow()
{
	auto bounds = sprite.getGlobalBounds();

	if (bounds.left < 0)
	{
		float spriteY = sprite.getPosition().y;
		sprite.setPosition(bounds.width / 2.0f, spriteY);
	}
	else if (bounds.left + bounds.width > window.getView().getSize().x)
	{
		float spriteY = sprite.getPosition().y;
		sprite.setPosition(window.getView().getSize().x - (bounds.width / 2.0f), spriteY);
	}
	if (bounds.top < 0)
	{
		float spriteX = sprite.getPosition().x;
		sprite.setPosition(spriteX, bounds.height / 2.0f);
	}
	else if (bounds.top + bounds.height > window.getView().getSize().y)
	{
		float spriteX = sprite.getPosition().x;
		sprite.setPosition(spriteX, window.getView().getSize().y - (bounds.height / 2.0f));
	}
}
