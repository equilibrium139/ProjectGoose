#include "Game.h"

void PollEvents(sf::Window& window);

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Project Goose", sf::Style::Titlebar | sf::Style::Close);
    Game game(window);

	sf::Clock frameTimer;

    while (window.isOpen())
    {
		PollEvents(window);
		window.clear();
        game.Go();
		window.display();
    }

    return 0;
}

void PollEvents(sf::Window& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		}
	}
}