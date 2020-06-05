#pragma once

#include <functional>
#include <memory>

#include <SFML/Graphics.hpp>

#include "Animation.h"
#include "Enemy.h"
#include "ResourceHolder.h"
#include "SpriteSheet.h"

class ZombieBird : public Enemy
{
public:
	ZombieBird(const sf::Vector2f& playerPos, sf::Vector2f spawnPos, float scale = 0.1f,
		float speed = 100.0f, int hitpoints = 1, bool targetPlayer = false);
	void Update(float dt) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override { target.draw(sprite, states); }
	sf::FloatRect GetBounds() const override { return sprite.getGlobalBounds(); }
	std::unique_ptr<Enemy> Clone() const override;
private:
	const static SpriteSheet& sheet()
	{
		static SpriteSheet flySheet = SpriteSheet(
			ResourceHolder::GetTexture("Assets/Textures/zombieBirdSheet.png"), 3, 1, 3);
		return flySheet;
	}
private:
	const sf::Vector2f& playerPos;
	sf::Sprite sprite;
	Animation fly;
	float speed;
	bool targetPlayer;
};