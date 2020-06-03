#include "Goose.h"
#include "VectorUtilities.h"

Goose::Goose(const sf::RenderWindow& window, sf::Vector2f position, float scale, float speed, int hitPoints)
	:window(window), animation(sprite, sheet()), speed(speed), hitPoints(hitPoints), shooter(window)
{
	auto bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
	sprite.setPosition(position);
	sprite.setScale(scale, scale);
}

void Goose::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	target.draw(sprite, states);
	shooter.DrawPoops(target);
}

void Goose::Update(float dt)
{
	ProcessMovementInput(dt);
	ClampToWindow();
	animation.Update(dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		auto bounds = sprite.getGlobalBounds();
		// offset to the butt area of the goose. Different depending on which direction it's facing
		const sf::Vector2f offset = sf::Vector2f(animation.IsFlipped() ? bounds.width / 2.0f : -bounds.width / 2.0f, bounds.height / 2.0f);
		shooter.AttemptShot(sprite.getPosition() + offset);
	}
	shooter.Update(dt);
}

void Goose::ProcessMovementInput(float dt)
{
	sf::Vector2f moveVec(0.0f, 0.0f);
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
		// mirror the goose sprite to make it look in the direction it's moving
		animation.SetFlip(true);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		moveVec.x += 1.0f;
		animation.SetFlip(false);
	}
	Normalize(moveVec);
	sprite.move(moveVec * speed * dt);
}

void Goose::DetectCollisions(ZombieSpawner& zombieSpawner)
{
	auto& zombies = zombieSpawner.GetZombies();
	auto& poops = shooter.GetPoops();
	auto myBounds = GetBounds();
	for (auto& zombie : zombies)
	{
		if (zombie->GetState() != Zombie::State::Dying && zombie->GetState() != Zombie::State::Dead)
		{
			// Detect collisions between goose and zombies
			auto zombieBounds = zombie->GetBounds();
			if (myBounds.intersects(zombieBounds))
			{
				TakeDamage();
			}
			// Detect collisions between zombies and poop
			bool zombieHit = std::any_of(poops.begin(), poops.end(),
				[&zombieBounds](Poop& poop) {
					bool collided = zombieBounds.intersects(poop.GetBounds());
					if (collided) { poop.collided = true; }
					return collided;
				});
			if (zombieHit)
			{
				zombie->TakeDamage();
			}
		}
	}
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