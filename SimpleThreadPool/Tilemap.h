#ifndef TILEMAP_H
#define TILEMAP_H

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Rectangle.h"

class Tilemap
{
public:
	Tilemap();
	~Tilemap();
	void init();

	void LoadMap(int arr[30][10], int t_mapWidth, int t_mapHeight);
	void Draw();
	void setMap(sf::RenderWindow& t_window);
	std::vector<Rectangles*> getTilesVec();
	std::vector<sf::Vector2f> getPlayerPosVec()
	{
		return m_playerPosVec;
	}
	void PushValsToVec()
	{
		for (int row = 0; row < m_mapWidth; row++)
		{
			for (int col = 0; col < m_mapHeigth; col++)
			{
				m_tileVecValues.push_back(lvl1[row][col]);
			}
		}
	}
private:

	std::vector<Rectangles*> m_tileVec;
	std::vector<sf::Vector2f> m_playerPosVec;
	static const int m_mapWidth = 30;
	static const int m_mapHeigth = 10;
	
	sf::Vector2f m_tilePosition = sf::Vector2f(0.0f, 0.0f);
	int m_tileSize = 32;
	int tilemap[m_mapWidth][m_mapHeigth];
	std::vector<int> m_tileVecValues;
	int lvl1[m_mapWidth][m_mapHeigth] = {
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,
1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,
1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,
1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,2,2,1,
1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,2,2,1,
1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
	};
};
#endif

