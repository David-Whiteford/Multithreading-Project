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
	//set up the tilemap for 30 x 30 level
	m_tileMap->make30SizeMap(m_mapWidth,m_mapHeight);
	m_tileMap->setMap(m_window);
	m_player.setPosition(m_tileMap->getPlayerPos());
	std::vector<Rectangles*> walls = m_tileMap->getTilesVec();
	int tileSize = m_tileMap->getNodeSize();
	//set up the ai graph
	m_gamePath->setNumNodes();
	m_gamePath->setNodeSize(tileSize);
	//add task for loading level into threadpool 
	m_threadPool.addTask(std::bind(&Path::initAStar, walls, m_gamePath));
	m_view.setCenter(sf::Vector2f(m_mapWidth * m_tileMap->getNodeSize() -70, m_mapHeight * m_tileMap->getNodeSize()-70));
	m_view.zoom(0.18f);
	//set up the enemies
	for (int i = 0; i < m_maxEnemies; i++) {
		int x, y = 0;
		x = randomInt(10, 5 * m_mapWidth - 1);
		y = randomInt(10, 5 * m_mapHeight - 1);
		m_npcVec.push_back(new NPC(m_window, m_deltaTime, sf::Vector2f(x, y), m_gamePath, m_tileMap->getNodeSize() /2, m_player));
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
	//check if multi threading is being used
	if (m_usemultiThreading == false) {
		aiMovement(m_npcVec,m_moveNpc);
	}
	else
	{
		//add task to calculate path with a star to the thread pool
 		m_threadPool.addTask(std::bind(aiMove, m_npcVec, m_moveNpc));
	}
	handleInputs();
	//create room 100 x 100
	if (m_createRoomTwo == true) {
		Room2Creation();
	}
	else if (m_createRoomThree == true) {

	}
}
void Game::render()
{ 
	//render all enemies and graph tiles
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
	//check if the ai should move
	if (t_moveNpc) {
		for (int i = 0; i < t_npcVec.size(); i++)
		{
			//call update to move ai
			t_npcVec[i]->update();
		}
	}
}

void Game::handleInputs()
{
	//check the input and set bool
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
	//set up view
	m_view.zoom(3.0f);
	sf::Vector2i offset = sf::Vector2i(110, 120);
	m_view.setCenter(sf::Vector2f(m_mapWidth * m_tileMap->getNodeSize() + offset.x, m_mapHeight * m_tileMap->getNodeSize()+ offset.y));
	//set new map widths
	m_mapWidth = 100;
	m_mapHeight = 100;
	m_maxEnemies = 100;
	//set up the tilemap for 100 x 100 level
	m_tileMap->make100SizeMap(m_mapWidth, m_mapHeight);
	m_tileMap->setMap(m_window);
	//get walls and set up the game graph
	std::vector<Rectangles*> walls = m_tileMap->getTilesVec();
	m_gamePath->deleteGraph();
	m_gamePath->setMapSize(m_mapWidth, m_mapHeight);
	m_gamePath->setNumNodes();
	m_gamePath->initAStar(walls, m_gamePath);
	//m_threadPool.addTask(std::bind(&Path::initAStar, walls, m_gamePath));
	m_player.setPosition(m_tileMap->getPlayerPos());
	//set up the all enemies
	for (int i = 0; i < m_maxEnemies; i++) {
		int x, y = 0;
		x = randomInt(10, 5 * m_mapWidth - 1);
		y = randomInt(10, 5 * m_mapHeight - 1);
		m_npcVec.push_back(new NPC(m_window, m_deltaTime, sf::Vector2f(x, y), m_gamePath, m_tileMap->getNodeSize() / 2, m_player));
	}
	m_createRoomTwo = false;
}


