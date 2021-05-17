#include "RayCast.h"

Raycast::Raycast()
{
	m_rayLines[0].color = sf::Color::White;
	m_rayLines[1].color = sf::Color::White;
}

Raycast::~Raycast()
{
}

void Raycast::hit(sf::Vector2f t_targetPos, float t_targetSize)
{
}

void Raycast::setRayVals(sf::Vector2f t_startPos, sf::Vector2f t_direction, float t_length)
{
	//set up the ray cast position,direction ,ray length and ray end position
	m_position = t_startPos;
	m_direction = t_direction;
	m_rayLength = t_length;
	m_rayEndPos = m_position + (m_direction * (m_rayLength));
	
}

sf::VertexArray Raycast::drawArray()
{
	//set up the rays 
	sf::VertexArray ray(sf::LinesStrip, 2);
	ray[0].position = m_position;
	ray[1].position = m_position + (m_direction * (m_rayLength));
	return ray;
}
bool Raycast::intersectsRect(sf::Vector2f p1, sf::Vector2f p2)
{
	return false;
}

sf::Vector2f Raycast::getEndPoint()
{
	return m_rayEndPos;
}
