#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& window)
	:wnd(window),
	player(wnd),
	background("Assets/Textures/background.jpg", wnd),
	zombieSpawner(wnd, player.GetPosition())
{
	backgroundMusic.openFromFile("Assets/Sounds/bgmusic.ogg");
	backgroundMusic.setLoop(true);
	backgroundMusic.play();
	SetWindowView();
	std::cout << wnd.getView().getSize().x + 10.0f << '\n';
	zombieSpawner.SetSpawnPosition({ wnd.getView().getSize().x + 20.0f, wnd.getView().getSize().y - 175.0f });
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

void Game::DetectCollisions()
{
	player.DetectCollisions(zombieSpawner);
}


void Game::Go()
{
	if (timeSinceLastCheckedCollision > collisionCheckInterval)
	{
		DetectCollisions();
		timeSinceLastCheckedCollision = 0.0f;
	}
	Update();
	Draw();
}

void Game::Update()
{
	dt = frameTimer.restart().asSeconds();

	timeSinceLastCheckedCollision += dt;

	player.Update(dt);
	background.Update(dt);
	zombieSpawner.Update(dt);
}

void Game::Draw()
{
	wnd.draw(background);
	zombieSpawner.DrawZombies(wnd);
	wnd.draw(player);
}