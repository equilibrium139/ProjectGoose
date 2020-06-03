#include "Game.h"

#include <iostream>

#include "ZombieProjectile.h"

Game::Game(sf::RenderWindow& window)
	:wnd(window),
	player(wnd),
	background("Assets/Textures/background.jpg", wnd),
	zombieSpawner(player.GetPosition(), {}, ZombieSpawner::ZombieSpawnBehavior{ sf::Vector2f(0.0f, 0.0f), 6.0f, 10.0f, 0.3f, 75.0f, 3 })
{
	backgroundMusic.openFromFile("Assets/Sounds/bgmusic.ogg");
	backgroundMusic.setLoop(true);
	backgroundMusic.play();
	SetWindowView();
	std::cout << wnd.getView().getSize().x + 10.0f << '\n';
	zombieSpawner.SetMinionSpawnPosition({ wnd.getView().getSize().x + 20.0f, wnd.getView().getSize().y - 125.0f });
	zombieSpawner.SetGiantSpawnPosition({ wnd.getView().getSize().x + 20.0f, wnd.getView().getSize().y - 200.0f });
}

void Game::SetWindowView()
{
	float bgWidth = background.Width();
	float bgHeight = background.Height();
	sf::View bgView(sf::Vector2f(bgWidth / 2.0f, bgHeight / 2.0f), sf::Vector2f(bgWidth, bgHeight));
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
	ZombieProjectile::UpdateAll(dt);
}

void Game::Draw()
{
	wnd.draw(background);
	zombieSpawner.DrawZombies(wnd);
	ZombieProjectile::DrawAll(wnd);
	wnd.draw(player);
}