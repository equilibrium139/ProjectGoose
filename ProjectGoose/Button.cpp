#include "Button.h"
#include "ResourceHolder.h"
#include <iostream>


Button::Button(const sf::RenderWindow& wnd, const std::string& content, const sf::Vector2f& pos, const sf::Color& c, unsigned int size)
	:window(wnd), text(content, ResourceHolder::GetFont("Assets/Fonts/ds_goose.ttf"))
{
	text.setFillColor(c);
	text.setPosition(pos);
	text.setCharacterSize(size);
}

void Button::SetOnClick(std::function<void(void)> func)
{
	onClick = func;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(text, states);
}

void Button::Update()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		auto mousePos = sf::Mouse::getPosition(window);
		auto mouseWorldPos = window.mapPixelToCoords(mousePos);
		auto bounds = text.getGlobalBounds();
		if (bounds.contains((float)mouseWorldPos.x, (float)mouseWorldPos.y))
		{
			onClick();
		}
	}
}
