#include "Game.h"

#include <iostream>

#include "ZombieProjectile.h"
#include "ZombieBird.h"

Game::Game(sf::RenderWindow& window)
	:wnd(window),
	player(wnd),
	background("Assets/Textures/background.jpg", wnd),
	loseBackgroundTexture(ResourceHolder::GetTexture("Assets/Textures/menuBackground.jpg")),
	play(wnd, "Play", { 600, 400 }, sf::Color::Red)
{
	backgroundMusic.openFromFile("Assets/Sounds/bgmusic.ogg");
	backgroundMusic.setLoop(true);
	backgroundMusic.play();
	play.SetOnClick([this]() { gameStarted = true; });
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
		0.1f, 100.0f, 1, true), 6.0f, 20.0f);
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
	if (gameStarted)
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
	else
	{
		play.Update();
	}
}

void Game::Draw()
{
	if (gameStarted)
	{
		wnd.draw(background);
		EnemySpawner::DrawAllEnemies(wnd);
		ZombieProjectile::DrawAll(wnd);
		wnd.draw(player);
	}
	else
	{
		wnd.draw(play);
	}
}