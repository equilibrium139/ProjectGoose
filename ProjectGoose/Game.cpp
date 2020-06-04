#include "Game.h"

#include <iostream>

#include "ZombieProjectile.h"

Game::Game(sf::RenderWindow& window)
	:wnd(window),
	player(wnd),
	background("Assets/Textures/background.jpg", wnd),
	minionPrototype(player.GetPosition()),
	giantPrototype(player.GetPosition(), {}, 0.30f, 75.0f, 3),
	zombieSpawner(EnemySpawner::EnemySpawnBehavior( &minionPrototype ), EnemySpawner::EnemySpawnBehavior( &giantPrototype, 5.0f, 6.0f ))
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
	if (player.IsDead())
	{
		std::cout << "You suck balls\n";
	}
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
	zombieSpawner.DrawEnemies(wnd);
	ZombieProjectile::DrawAll(wnd);
	wnd.draw(player);
}