#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>

class Raycast
{
public:
	Raycast();
	~Raycast();
	//set up the raycast and collisions
	void hit(sf::Vector2f t_targetPos, float t_targetSize);
	void setRayVals(sf::Vector2f t_startPos, sf::Vector2f t_direction, float t_length);
	sf::VertexArray drawArray();
	bool intersectsRect(sf::Vector2f p1, sf::Vector2f p2);
	sf::Vector2f getEndPoint();
private:
	//set the ray length,direction,position and rays
	float m_rayLength = 100.0f;
	sf::Vector2f m_direction;
	sf::Vector2f m_position;
	sf::Vertex m_rayLines[2];
	sf::Vector2f m_rayEndPos;
	bool m_rectCollisions = false;
};

