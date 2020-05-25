#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& window)
	:wnd(window),
	player(resourceHolder, wnd),
	background("Assets/Textures/background.jpg", wnd),
	zombie(resourceHolder, wnd)
{
	SetWindowView();
}

void Game::SetWindowView()
{
	float bgWidth = background.Width();
	float bgHeight = background.Height();
	std::cout << bgWidth << '\n';
	sf::View bgView(sf::Vector2f(bgWidth / 2.0f, bgHeight / 2.0f), sf::Vector2f(bgWidth, bgHeight));
	std::cout << bgView.getSize().x << '\n';
	wnd.setView(bgView);
	std::cout << wnd.getView().getSize().x << '\n';
}


void Game::Go()
{
	Update();
	Draw();
}

void Game::Update()
{
	dt = frameTimer.restart().asSeconds();

	player.Update(dt);
	background.Update(dt);
	zombie.Update(dt);
}

void Game::Draw()
{
	wnd.draw(background);
	wnd.draw(zombie);
	wnd.draw(player);
}