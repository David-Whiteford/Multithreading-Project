#pragma once
#include "Path.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "Transform.h"
#include <stdlib.h>
#include <ctime>
#include "ThreadPool.h"
#include "MyEnums.h"

class NPC : public GameObject
{
public:
	NPC(sf::RenderWindow& t_window, sf::Time& t_deltaTime, sf::Vector2f t_position, Path* t_gamePath,int t_size, sf::RectangleShape t_player);
	~NPC();
	void enemyInit();
	void setSpeed(float t_speed);
	//get the player node , set position and get position
	int getPlayerNode(sf::Vector2f t_playerPosition)
	{
		return m_gamePath->nodePos(t_playerPosition);
	}
	void setPosition(sf::Vector2f t_pos);
	sf::Vector2f getPosition()
	{
		return m_enemy.getPosition();
	}
	//sets the path
	void setPath(Path* t_gamePath)
	{
		m_gamePath = t_gamePath;
	}
	//set up the functions for the game npcs
	void update();
	void enemyMovement(sf::Time t_deltaTime);
	void moveEnemy(sf::Time t_deltaTime);
	void draw();
	void clearGraphPath()
	{
		//delete game path and clearing them
		delete m_gamePath;
		for (int i = 0; i < graphPath.size(); i++) {
			delete graphPath[i];
		}
		graphPath.clear();
	}
	GameObject* myGameObject;

private:
	//get the end position for the npc, speed ,time,transformn
	sf::Vector2f m_endPos = sf::Vector2f(100, 50);
	float m_speed =0.1f;
	sf::Time m_time;
	Transform m_transform;
	//sets the graph position, path, window and enemies
	Transform::Position graphPos;
	std::vector<Node*> graphPath;
	sf::RenderWindow& m_window;
	sf::RectangleShape m_enemy;
	//sets teh game path, path vector, size ,enemy nodes,player nodes
	Path* m_gamePath;
	sf::Vector2f graphPathVec;
	int m_size = 0;
	int m_enemyNode = 0;
	int m_playerNode = 0;
	//set the start node and end nodes
	int startNode = 103;
	int endNode = 2227;
	//sets the position and sets the walls and player and time
	sf::Vector2f m_position = sf::Vector2f(0, 0);
	std::vector<sf::RectangleShape> m_walls;
	sf::RectangleShape m_player;
	sf::Time& m_deltaTime;
};

