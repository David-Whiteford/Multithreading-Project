#ifndef GAME_H
#define GAME_H
#include "Tilemap.h"
#include <SFML/Graphics.hpp>
#include "MyEnums.h"
#include "Path.h"
#include "ThreadPool.h"
#include "NPC.h"
class Game
{
public:
	Game();
	~Game();

	void run();

private:
	void init();
	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();
	void aiMovement(std::vector<NPC*> t_npcVec, bool t_moveNpc);
	void handleInputs();
	void Room2Creation();
	//variables needed
	Tilemap* m_tileMap;
	ThreadPool m_threadPool;
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::Event event;
	sf::RenderWindow m_window; // main SFML window
	//variabvles for the map size and nodes
	int m_enemyNode = 0;
	int m_mapWidth = 30;
	int m_mapHeight = 30;
	//set up the astar grid
	Path* m_gamePath = new Path(m_window, m_mapWidth, m_mapHeight);
	sf::Time m_deltaTime;
	bool m_usemultiThreading = true;
	sf::RectangleShape m_player;
	int m_maxEnemies = 30;
	//set up the ai and view along with variables
	sf::Vector2i m_mapMax = sf::Vector2i(400, 400);
	int m_pos = 24;
	std::vector<NPC*> m_npcVec;
	bool m_moveNpc = false;
	sf::View m_view;
	bool m_createRoomTwo, m_createRoomThree = false;
	std::vector<Rectangles*> m_walls;
};
#endif