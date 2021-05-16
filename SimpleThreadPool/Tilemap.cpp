#include "Tilemap.h"

Tilemap::Tilemap()
{
}
Tilemap::~Tilemap()
{
}


void Tilemap::setMap(sf::RenderWindow& t_window)
{
	int type = 0;
	int x = 0;
	int y = 0;
	for (int i = 0; i < m_tileVecValues.size(); i++)
	{
		type = m_tileVecValues[i];
		switch (type)
		{
		case 0:
			break;
		case 1:
			m_tileVec.push_back(new Rectangles(t_window, m_tileSize,
				sf::Vector2f(x * m_tileSize, y * m_tileSize), 1, sf::Color::White));
			break;
		case 3:
			m_tileVec.push_back(new Rectangles(t_window, m_tileSize,
				sf::Vector2f(x * m_tileSize, y * m_tileSize), 3, sf::Color::Red));
			break;
		default:
			break;
		}
		x++;
		if (x == m_mapWidth)
		{
			x = 0;
			y++;
		}

	}
}
std::vector<Rectangles*> Tilemap::getTilesVec()
{
	return m_tileVec;
}

