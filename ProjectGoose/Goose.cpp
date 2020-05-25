#include "Goose.h"
#include "Vec2.h"

Goose::Goose(ResourceHolder& resourceHolder, const sf::RenderWindow& in_window)
	:texture(resourceHolder.GetTexture("Assets/Textures/gooseSpritesheet.png")), 
	 animation(texture, 3, 3, 1), window(in_window)
{
	/*sprite.setTexture(texture);
	sprite.setTextureRect({ 0, currentFrame * (int)texture.getSize().y / 3, (int)texture.getSize().x, (int)texture.getSize().y / 3 });
	sprite.setScale(scale, scale);
	auto bounds = sprite.getLocalBounds();
	sprite.setOrigin({ bounds.width / 2.0f, bounds.height / 2.0f });*/
	animation.setScale(scale, scale);
}

void Goose::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	//target.draw(sprite, states);
	target.draw(animation, states);
	shooter.DrawPoops(target);
}

void Goose::Update(float dt)
{
	/*timeSinceLastAnimationChange += dt;
	if (timeSinceLastAnimationChange >= animationChangeTime)
	{
		currentFrame++;
		currentFrame %= nFrames;
		sprite.setTextureRect({ 0, currentFrame * (int)texture.getSize().y / 3, (int)texture.getSize().x, (int)texture.getSize().y / 3 });
		timeSinceLastAnimationChange = 0.0f;
	}*/
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
		animation.setScale(-scale, scale);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		moveVec.x += 1.0f;
		animation.setScale(scale, scale);
	}
	animation.move(moveVec.Normalize() * speed * dt);
	ClampToWindow();

	animation.Update(dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		shooter.AttemptShot(animation.getPosition() - sf::Vector2f(animation.GetBounds().width / 2.0f, -animation.GetBounds().height / 2.0f));
	}
	shooter.Update(dt);
}

void Goose::ClampToWindow()
{
	auto bounds = animation.GetBounds();

	if (bounds.left < 0)
	{
		float spriteY = animation.getPosition().y;
		animation.setPosition(bounds.width / 2.0f, spriteY);
	}
	else if (bounds.left + bounds.width > window.getView().getSize().x)
	{
		float spriteY = animation.getPosition().y;
		animation.setPosition(window.getView().getSize().x - (bounds.width / 2.0f), spriteY);
	}
	if (bounds.top < 0)
	{
		float spriteX = animation.getPosition().x;
		animation.setPosition(spriteX, bounds.height / 2.0f);
	}
	else if (bounds.top + bounds.height > window.getView().getSize().y)
	{
		float spriteX = animation.getPosition().x;
		animation.setPosition(spriteX, window.getView().getSize().y - (bounds.height / 2.0f));
	}
}