#include "ScrollingBackground.h"

ScrollingBackground::ScrollingBackground( const std::string& textureFile, const sf::RenderWindow& inWindow)
	:window(inWindow)
{
	texture.loadFromFile(textureFile);


	original.setTexture(texture);
	auto bounds = original.getLocalBounds();
	original.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
	original.move(bounds.width / 2.0f, bounds.height / 2.0f);

	mirrored.setTexture(texture);
	mirrored.scale(-1.0f, 1.0f); //this will mirror the image
	mirrored.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
	mirrored.move(bounds.width / 2.0f, bounds.height / 2.0f);
}

void ScrollingBackground::Update(float dt)
{
	float distance = speed * dt;
	original.move(distance, 0.0f);
	mirrored.move(distance, 0.0f);
	auto originalBounds = original.getGlobalBounds();
	if (originalBounds.left + originalBounds.width <= window.getView().getSize().x)
	{
		mirrored.setPosition(original.getPosition().x + originalBounds.width - 5, mirrored.getPosition().y);
		std::swap(original, mirrored);
	}
}

void ScrollingBackground::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(original, states);
	target.draw(mirrored, states);
}
