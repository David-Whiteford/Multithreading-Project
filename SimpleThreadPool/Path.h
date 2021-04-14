#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "AStar/Graph.h"
#include "AStar/NodeData.h"
#include "Rectangle.h"
#include "Transform.h"
#include "RayCast.h"
typedef GraphNode<NodeData, int> Node;
class Path
{
public:
	Path(sf::RenderWindow& t_window);
	~Path();
	void draw();
	void neighbourAlgor();
	void clearAStar();
	void initAStar(std::vector<Rectangles*>& t_rects);
	void update();
	void setPath();
	void setNewPath();
	void setNumNodes(int t_numNodes)
	{
		m_numNodes = t_numNodes;
	}
	void newPath(int t_start, int t_end);
	std::vector<Node*>& getGraphPath();
	int nodePos(sf::Vector2f position);

private:
	sf::RenderWindow& m_window;
	std::map<std::string, int> nodeMap;
	Graph<NodeData, int>* graph;
	int endNode = 2237;
	int startNode = 103;
	Raycast m_raycastUp;
	Transform m_transform;
	std::vector<Node*> graphPath;
	int m_numNodes = 900;
	std::vector<std::vector<Node*>> paths;
	NodeData nodeData;
	int nodeIndex{ 0 };

	std::vector<sf::RectangleShape> m_nodeSquare;
	int val = 0;
	int m_rows = 30;
	int m_cols = 30;
	

	sf::RectangleShape m_nodeShape[2500];
	int m_nodeSize = 32;
};
