#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "AStar/Graph.h"
#include "AStar/NodeData.h"
#include "Rectangle.h"
#include "Transform.h"
#include "RayCast.h"
#include "Collisions.h"
#include "Debug.h"
typedef GraphNode<NodeData, int> Node;
class Path
{
public:
	Path(sf::RenderWindow& t_window,int t_mapWidth, int t_mapHeigth);
	~Path();
	void draw();
	void neighbourAlgor();
	void setMapSize(int t_mapWidth, int m_mapHeigth)
	{
		m_rows = t_mapWidth;
		m_cols = m_mapHeigth;
	}
	void clearAStar();
	void setColor(sf::Color t_color, std::vector<Node*> &t_graphPath)
	{
		for (int i = 0; i < t_graphPath.size(); i++)
		{
			m_nodeShape[t_graphPath[i]->m_data.index].setFillColor(t_color);
			t_graphPath[i]->m_data.passable = false;
		}
	}
	//functions to start A*, and update,and set the path
	void initAStar(std::vector<Rectangles*>& t_rects);
	void update();
	void setPath();
	void setNumNodes()
	{
		m_numNodes = m_rows * m_cols;
	}
	void deleteGraph()
	{
		delete graph;
	}

	void newPath(int t_start, int t_end);
	std::vector<Node*>& getGraphPath();
	int nodePos(sf::Vector2f position);
	void setNodeSize(int t_size);

private:
	std::vector<sf::RectangleShape> m_nodeShape;
	Collisions m_colliders;
	sf::RenderWindow& m_window;
	std::map<std::string, int> nodeMap;
	Graph<NodeData, int>* graph;
	int endNode = 2237;
	int startNode = 103;
	Raycast m_raycastUp;
	Transform m_transform;
	std::vector<Node*> graphPath;
	int m_numNodes = 0;
	std::vector<NodeData> m_gridNodes;
	NodeData nodeData;
	int nodeIndex{ 0 };
	int val = 0;
	int m_rows = 0;
	int m_cols = 0;
	int m_nodeSize = 0;
};
