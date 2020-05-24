#include "Game.h"

Game::Game(sf::RenderWindow& window)
	:wnd(window),
	player(wnd)
{
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
}

void Game::Draw()
{
	wnd.draw(player);
}
