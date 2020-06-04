#include "Game.h"

#include <iostream>

#include "ZombieProjectile.h"

Game::Game(sf::RenderWindow& window)
	:wnd(window),
	player(wnd),
	background("Assets/Textures/background.jpg", wnd),
	loseBackgroundTexture(ResourceHolder::GetTexture("Assets/Textures/menuBackground.jpg")),
	minionPrototype(player.GetPosition()),
	giantPrototype(player.GetPosition(), {}, 0.30f, 75.0f, 3),
	zombieMinionSpawner(EnemySpawner::EnemySpawnBehavior(&minionPrototype)),
	zombieGiantSpawner(EnemySpawner::EnemySpawnBehavior(&giantPrototype, 5.0f, 6.0f))
{
	backgroundMusic.openFromFile("Assets/Sounds/bgmusic.ogg");
	backgroundMusic.setLoop(true);
	backgroundMusic.play();
	loseBackground.setTexture(loseBackgroundTexture);
	SetWindowView();
	loseBackground.setScale(background.Width() / loseBackground.getLocalBounds().width,
		background.Height() / loseBackground.getLocalBounds().height);
	std::cout << wnd.getView().getSize().x + 10.0f << '\n';
	zombieMinionSpawner.SetSpawnPosition({ wnd.getView().getSize().x + 20.0f, wnd.getView().getSize().y - 125.0f });
	zombieGiantSpawner.SetSpawnPosition({ wnd.getView().getSize().x + 20.0f, wnd.getView().getSize().y - 200.0f });
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
		zombieMinionSpawner.Update(dt);
		zombieGiantSpawner.Update(dt);
		EnemySpawner::UpdateAllEnemies(dt);
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