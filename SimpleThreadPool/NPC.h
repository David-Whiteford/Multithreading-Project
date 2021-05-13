#pragma once
#include "Path.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "Transform.h"
#include <stdlib.h>
#include <ctime>
class NPC : public GameObject
{
public:
	NPC(sf::RenderWindow& t_window, sf::Time& t_deltaTime, sf::Vector2f t_position, Path* t_gamePath,int t_size, sf::RectangleShape t_player);
	~NPC();
	void enemyInit();
	void setSpeed(float t_speed);
	int getPlayerNode(sf::Vector2f t_playerPosition)
	{
		return m_gamePath->nodePos(t_playerPosition);
		
	}
	void setPosition(sf::Vector2f t_pos);
	sf::Vector2f getPosition()
	{
		return m_enemy.getPosition();
	}
	void update();
	void enemyMovement(sf::Time t_deltaTime);
	void moveEnemy(sf::Time t_deltaTime);
	void draw();

	GameObject* myGameObject;

private:
	sf::Vector2f m_endPos = sf::Vector2f(100, 50);
	int m_doOncePatrol = 0;
	float m_speed = 1.0f;
	sf::Time m_time;
	Transform m_transform;
	Transform::Position graphPos;
	std::vector<Node*> graphPath;
	sf::RenderWindow& m_window;
	sf::RectangleShape m_enemy;
	Path* m_gamePath;
	sf::Vector2f graphPathVec;
	std::vector<int> m_startNodes;
	std::vector<int> m_endNodes;
	int m_size = 0;
	int m_enemyNode = 0;
	int m_playerNode = 0;
	int startNode = 103;
	int endNode = 2227;
	sf::Vector2f m_position = sf::Vector2f(0, 0);
	std::vector<sf::RectangleShape> m_walls;
	sf::RectangleShape m_player;
	sf::Time& m_deltaTime;
};

