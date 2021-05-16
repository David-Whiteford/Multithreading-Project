#include "Game.h"
#include <ThreadPool.h>
#include <iostream>
static double const MS_PER_UPDATE = 10.0;

void aiMove(std::vector<NPC*> &t_npcVec, bool t_moveNpc)
{
	if (t_moveNpc) {
		for (int i = 0; i < t_npcVec.size(); i++)
		{
			t_npcVec[i]->update();
		}
	}
}
Game::Game() :
	m_window{ sf::VideoMode{ desktop.width, desktop.height, desktop.bitsPerPixel }, "SFML Game" }
{
	init();
	m_tileMap->make30SizeMap(m_mapWidth,m_mapHeight);
	m_tileMap->setMap(m_window);
	sf::RectangleShape playerPos = m_tileMap->getPlayerPos();
	m_player.setPosition(playerPos.getPosition().x, playerPos.getPosition().y);
	std::vector<Rectangles*> walls = m_tileMap->getTilesVec();
	int tileSize = m_tileMap->getNodeSize();
	m_gamePath->setNumNodes();
	m_gamePath->setNodeSize(tileSize);
	//m_gamePath->initAStar(walls);
	m_threadPool.addTask(std::bind(&Path::initAStar, walls, m_gamePath));
	m_view.setCenter(sf::Vector2f(m_mapWidth * m_tileMap->getNodeSize() -70, m_mapHeight * m_tileMap->getNodeSize()-70));
	m_view.zoom(0.18f);
	for (int i = 0; i < m_maxEnemies; i++)
	{
		int x, y = 0;
		x = randomInt(10,5 * m_mapWidth-1 );
		y = randomInt(10, 5 * m_mapHeight -1);
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
	
	if (m_usemultiThreading == false) {
		aiMovement(m_npcVec,m_moveNpc);
	}
	else
	{
		m_threadPool.addTask(std::bind(aiMove, m_npcVec, m_moveNpc));
	}
	handleInputs();
	if (m_createRoomTwo == true) {
		Room2Creation();
	}
	else if (m_createRoomThree == true) {

	}
}
void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_window.setView(m_view);
	m_gamePath->draw();
	for (int i = 0; i < m_npcVec.size(); i++)
	{
		m_npcVec[i]->draw();
	}
	m_window.display();
}

void Game::aiMovement(std::vector<NPC*> t_npcVec, bool t_moveNpc)
{
	if (t_moveNpc) {
		for (int i = 0; i < t_npcVec.size(); i++)
		{
			t_npcVec[i]->update();
		}
	}
}

void Game::handleInputs()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_moveNpc = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		m_createRoomTwo = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		m_createRoomTwo = false;
	}
}

void Game::Room2Creation()
{
	m_createRoomTwo = false;

	m_view.zoom(2.0f);
	int currentUnitNum = m_maxEnemies;
	m_mapWidth = 100;
	m_mapHeight = 100;
	m_maxEnemies = 100;
	m_tileMap->make100SizeMap(m_mapWidth, m_mapHeight);
	m_tileMap->setMap(m_window);
	std::vector<Rectangles*> walls = m_tileMap->getTilesVec();
	m_gamePath->deleteGraph();
	m_gamePath->setMapSize(m_mapWidth, m_mapHeight);
	m_gamePath->setNumNodes();
	m_threadPool.addTask(std::bind(&Path::initAStar, walls,m_gamePath));
	for (int i = currentUnitNum; i < m_maxEnemies; i++) {
		int x, y = 0;
		x = randomInt(5, 5 * m_mapWidth - 1);
		y = randomInt(5, 5 * m_mapHeight - 1);
		m_startingPos.push_back(sf::Vector2f(x, y));
		m_npcVec.push_back(new NPC(m_window, m_deltaTime, m_startingPos[i], m_gamePath, m_tileMap->getNodeSize() / 2, m_player));
	}
}



