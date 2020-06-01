#include "Goose.h"
#include "VectorUtilities.h"

//Goose::Goose(const sf::RenderWindow& in_window)
//	:animation(ResourceHolder::GetTexture("Assets/Textures/gooseSpritesheet.png"), 3, 3, 1), window(in_window), shooter(in_window)
//{
//	auto bounds = animation.GetBounds();
//	transform.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
//	transform.setScale(scale, scale);
//}

Goose::Goose(const sf::RenderWindow& window, sf::Vector2f position, float scale, float speed, int hitPoints)
	:window(window), animation(ResourceHolder::GetTexture("Assets/Textures/gooseSpritesheet.png"), 3, 3, 1), 
	 speed(speed), hitPoints(hitPoints), shooter(window)
{
	auto bounds = animation.GetBounds();
	transform.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f); // set origin to center of sprite
	transform.setPosition(position);
	transform.setScale(scale, scale);
}

void Goose::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	states.transform *= transform.getTransform();
	target.draw(animation, states);
	shooter.DrawPoops(target);
}

void Goose::Update(float dt)
{
	ProcessMovementInput(dt);
	ClampToWindow();
	animation.Update(dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		auto bounds = GetBounds();
		// offset to the butt area of the goose. Different depending on which direction it's facing
		sf::Vector2f offset = sf::Vector2f(transform.getScale().x > 0 ? -bounds.width / 2.0f : bounds.width / 2.0f, bounds.height / 2.0f);
		shooter.AttemptShot(transform.getPosition() + offset);
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
		transform.setScale(-std::abs(transform.getScale().x), transform.getScale().y);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		moveVec.x += 1.0f;
		transform.setScale(std::abs(transform.getScale().x), transform.getScale().y);
	}
	Normalize(moveVec);
	transform.move(moveVec * speed * dt);
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
	auto bounds = transform.getTransform().transformRect(animation.GetBounds());

	if (bounds.left < 0)
	{
		float spriteY = transform.getPosition().y;
		transform.setPosition(bounds.width / 2.0f, spriteY);
	}
	else if (bounds.left + bounds.width > window.getView().getSize().x)
	{
		float spriteY = transform.getPosition().y;
		transform.setPosition(window.getView().getSize().x - (bounds.width / 2.0f), spriteY);
	}
	if (bounds.top < 0)
	{
		float spriteX = transform.getPosition().x;
		transform.setPosition(spriteX, bounds.height / 2.0f);
	}
	else if (bounds.top + bounds.height > window.getView().getSize().y)
	{
		float spriteX = transform.getPosition().x;
		transform.setPosition(spriteX, window.getView().getSize().y - (bounds.height / 2.0f));
	}
}