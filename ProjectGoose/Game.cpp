#include "Game.h"

#include <iostream>

#include "ZombieProjectile.h"
#include "ZombieBird.h"

Game::Game(sf::RenderWindow& window)
	:wnd(window),
	player(wnd),
	background("Assets/Textures/background.jpg", wnd),
	loseBackgroundTexture(ResourceHolder::GetTexture("Assets/Textures/menuBackground.jpg"))
{
	backgroundMusic.openFromFile("Assets/Sounds/bgmusic.ogg");
	backgroundMusic.setLoop(true);
	backgroundMusic.play();
	loseBackground.setTexture(loseBackgroundTexture);
	SetWindowView();
	loseBackground.setScale(background.Width() / loseBackground.getLocalBounds().width,
		background.Height() / loseBackground.getLocalBounds().height);

	//Zombie minion
	sf::Vector2f minionSpawnPos(wnd.getView().getSize().x + 20.0f, wnd.getView().getSize().y - 125.0f);
	enemySpawners.emplace_back(std::make_unique<Zombie>(player.GetPosition(), minionSpawnPos));

	// Zombie giant
	sf::Vector2f giantSpawnPos(wnd.getView().getSize().x + 20.0f, wnd.getView().getSize().y - 200.0f);
	enemySpawners.emplace_back(std::make_unique<Zombie>(player.GetPosition(), 
		giantSpawnPos, 0.3f, 75.0f, 3), 5.0f, 6.0f);

	//Zombie bird
	sf::Vector2f birdSpawnPos(wnd.getView().getSize().x + 20.0f, 200.0f);
	enemySpawners.emplace_back(std::make_unique<ZombieBird>(player.GetPosition(), birdSpawnPos,
		0.1f, 100.0f, 1, true));
}

void Game::SetWindowView()
{
	float bgWidth = background.Width();
	float bgHeight = background.Height();
	sf::View bgView(sf::Vector2f(bgWidth / 2.0f, bgHeight / 2.0f), sf::Vector2f(bgWidth, bgHeight));
	wnd.setView(bgView);
}

void Game::DetectCollisions()
{
	player.DetectCollisions();
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
	if (!player.IsDead())
	{
		dt = frameTimer.restart().asSeconds();

		timeSinceLastCheckedCollision += dt;

		player.Update(dt);
		background.Update(dt);
		for (auto& spawner : enemySpawners)
		{
			spawner.Update(dt);
		}
		EnemySpawner::UpdateAllEnemies(dt, wnd);
		ZombieProjectile::UpdateAll(dt);
	}
}

void Game::Draw()
{
	if (!player.IsDead())
	{
		wnd.draw(background);
		EnemySpawner::DrawEnemies(wnd);
		ZombieProjectile::DrawAll(wnd);
		wnd.draw(player);
	}
	else
	{
		wnd.draw(loseBackground);
	}
}