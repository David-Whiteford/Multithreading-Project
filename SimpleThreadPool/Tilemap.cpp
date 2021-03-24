#include "Tilemap.h"

Tilemap::Tilemap()
{
	
	LoadMap(lvl1, 30, 10);

}
Tilemap::~Tilemap()
{
}
void Tilemap::LoadMap(int arr[m_mapWidth][m_mapHeigth], int t_mapWidth, int t_mapHeight)
{
	for (int row = 0; row < t_mapWidth; row++)
	{
		for (int col = 0; col < t_mapHeight; col++)
		{
			tilemap[row][col] = arr[row][col];
		}
	}
}
void Tilemap::Draw()
{
	for (int i = 0; i < m_tileVec.size(); i++)
	{
		m_tileVec[i]->draw();
	}
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
			m_tileVec.push_back(new Rectangles(t_window, m_tileSize,
				sf::Vector2f(x * m_tileSize, y * m_tileSize),0,sf::Color::Black));
			break;
		case 1:
			m_tileVec.push_back(new Rectangles(t_window, m_tileSize,
				sf::Vector2f(x * m_tileSize, y * m_tileSize), 0, sf::Color::White));
			break;
		case 2:
			m_tileVec.push_back(new Rectangles(t_window, m_tileSize,
				sf::Vector2f(x * m_tileSize, y * m_tileSize), 0, sf::Color::Yellow));
			m_playerPosVec.push_back(sf::Vector2f(x * m_tileSize, y * m_tileSize));
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

