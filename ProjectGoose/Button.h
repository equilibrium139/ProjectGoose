#pragma once

#include <functional>

#include <SFML/Graphics.hpp>

class Button : public sf::Drawable
{
public:
	Button(const sf::RenderWindow& wnd, const std::string& content, const sf::Vector2f& pos,  const sf::Color& c, unsigned int size = 30u);
	void SetOnClick(std::function<void(void)> func);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void Update();
private:
	std::function<void(void)> onClick;
	const sf::RenderWindow& window;
	sf::Text text;
};

