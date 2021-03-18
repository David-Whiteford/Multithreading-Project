#include "Game.h"
#include <ThreadPool.h>
#include <iostream>
static double const MS_PER_UPDATE = 10.0;
Game::Game() :
	m_window{ sf::VideoMode{ desktop.width, desktop.height, desktop.bitsPerPixel }, "SFML Game" }
{
	init();
	ThreadPool tp;
}


Game::~Game()
{
}


void Game::run()
{
	sf::Clock clock;
	sf::Int32 lag = 0;

	while (m_window.isOpen())
	{
		sf::Time dt = clock.restart();

		lag += dt.asMilliseconds();

		processEvents();

		while (lag > MS_PER_UPDATE)
		{
			update(MS_PER_UPDATE);
			lag -= MS_PER_UPDATE;
		}
		update(MS_PER_UPDATE);

		render();
	}
}


void Game::init()
{

}

void Game::processEvents()
{
}

void Game::update(double dt)
{



}

void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_window.display();
}

void Game::handleInputs()
{

}

