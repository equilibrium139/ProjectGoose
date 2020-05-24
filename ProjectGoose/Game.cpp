#include "Game.h"

Game::Game(sf::RenderWindow& window)
	:wnd(window)
{
}

void Game::Go()
{
	Update();
	Draw();
}

void Game::Update()
{
}

void Game::Draw()
{
}
