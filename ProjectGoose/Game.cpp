#include "Game.h"

Game::Game(sf::RenderWindow& window)
	:wnd(window),
	player(wnd),
	background("Assets/Textures/background.jpg", wnd)
{
	float bgWidth = background.Width();
	float bgHeight = background.Height();
	sf::View bgView(sf::Vector2f(bgWidth / 2.0f, bgHeight / 2.0f), sf::Vector2f(bgWidth, bgHeight));
	window.setView(bgView);
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
}

void Game::Draw()
{
	wnd.draw(background);
	wnd.draw(player);
}
