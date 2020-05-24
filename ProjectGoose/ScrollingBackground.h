#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class ScrollingBackground : public sf::Drawable
{
public:
	ScrollingBackground( const std::string& textureFile, const sf::RenderWindow& inWindow);
	void Update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	float Width() const { return original.getLocalBounds().width; }
	float Height() const { return original.getLocalBounds().height; }
private:
	const sf::RenderWindow& window;
	sf::Texture texture;
	sf::Sprite original;
	sf::Sprite mirrored;
	float speed = -50.0f;
};