#include "Game.h"
#include <ThreadPool.h>
#include <iostream>
static double const MS_PER_UPDATE = 10.0;
Game::Game() :
	m_window{ sf::VideoMode{ desktop.width, desktop.height, desktop.bitsPerPixel }, "SFML Game" }
{
	init();
	m_tileMap->PushValsToVec();
	m_tileMap->setMap(m_window);
	for (int i = 0; i < m_maxEnemies; i++) {
		int randX = rand() % 850 + 50;
		int randY = rand() % 850 + 50;
		m_startingPos.push_back(sf::Vector2f(randX, randY));
	}
	
	std::vector<Rectangles*> walls = m_tileMap->getTilesVec();

	m_gamePath->initAStar(walls);
	ThreadPool tp;
	for (int i = 0; i < m_maxEnemies; i++) {
		m_npcVec.push_back(new NPC(m_window, m_deltaTime, m_startingPos[i], m_gamePath));
	}

}


Game::~Game()
{
}


void Game::run()
{
	sf::Clock clock;
	sf::Clock gunClock;
	sf::Time oldTime = sf::Time::Zero;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds((1.f / 60.0f));

	while (m_window.isOpen())
	{
		m_deltaTime = clock.getElapsedTime() - oldTime;

		if (clock.getElapsedTime() > oldTime + timePerFrame)
		{
			processEvents();
			update(m_deltaTime);
			processEvents();
			oldTime = clock.getElapsedTime();
			render();
		}
	}
}


void Game::init()
{
	m_tileMap = new Tilemap();
}

void Game::processEvents()
{
}

void Game::update(sf::Time t_deltaTime)
{
	sf::RectangleShape player;
	player.setSize(sf::Vector2f(10, 10));
	player.setFillColor(sf::Color::Red);
	player.setPosition(50, 50);
	if (m_moveNpc)
	{
		for (int i = 0; i < m_npcVec.size(); i++)
		{
			m_npcVec[i]->update(player, m_deltaTime);
			
		}
	}
	
	handleInputs();
}

void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_tileMap->Draw();
	m_gamePath->draw();
	for (int i = 0; i < m_npcVec.size(); i++)
	{
		m_npcVec[i]->draw();
	}
	m_window.display();
}

void Game::handleInputs()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_moveNpc = true;
	}
}

