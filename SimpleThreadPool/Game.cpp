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
	sf::RectangleShape playerPos = m_tileMap->getPlayerPos();
	m_player.setSize(sf::Vector2f(5, 5));
	m_player.setFillColor(sf::Color::Red);
	m_player.setPosition(playerPos.getPosition().x, playerPos.getPosition().y);
	std::vector<Rectangles*> walls = m_tileMap->getTilesVec();
	int tileSize = m_tileMap->getNodeSize();
	m_gamePath->setNodeSize(tileSize);
	m_gamePath->initAStar(walls);
	ThreadPool tp;
	
	for (int i = 0; i < m_maxEnemies; i++)
	{
		int x, y = 0;
		x = randomInt(10,10 * 29);
		y = randomInt(10, 10 * 29);
		m_startingPos.push_back(sf::Vector2f(x, y));
	}
	for (int i = 0; i < m_maxEnemies; i++) {
		m_npcVec.push_back(new NPC(m_window, m_deltaTime, m_startingPos[i], m_gamePath, m_tileMap->getNodeSize() /2, m_player));
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
	if (m_moveNpc)
	{
		for (int i = 0; i < m_npcVec.size(); i++)
		{
			m_npcVec[i]->update();

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

