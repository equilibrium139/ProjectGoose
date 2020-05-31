#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Poop.h"

class Shooter
{
public:
	Shooter(const sf::RenderWindow& wnd, float cooldown = 1.0f);
	void AttemptShot(sf::Vector2f position);
	void Update(float dt);
	void DrawPoops(sf::RenderTarget& target) const;
	std::vector<Poop>& GetPoops() { return poops; }
private:
	float screenBottom;
	float cd;
	float timeSinceLastShot;
	std::vector<Poop> poops;
	sf::SoundBuffer splatterSoundBuffer;
	sf::Sound splatterSound;
};