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
	//sets teh number for row and cols
	void setMapSize(int t_mapWidth, int m_mapHeigth)
	{
		m_rows = t_mapWidth;
		m_cols = m_mapHeigth;
	}
	//delete node vec
	void deleteNodeShapes()
	{
		m_nodeShape.clear();
	}
	void clearAStar();
	//sets the color of the path
	void setColor(sf::Color t_color, std::vector<Node*> &t_graphPath)
	{
		for (int i = 0; i < t_graphPath.size(); i++)
		{
			m_nodeShape[t_graphPath[i]->m_data.index].setFillColor(t_color);
		}
	}
	//functions to start A*, and update,and set the path
	static void initAStar(std::vector<Rectangles*>& t_rects, Path *t_path);
	void update();
	void setPath();
	//set the number of nodes
	void setNumNodes()
	{
		m_numNodes = m_rows * m_cols;
	}
	//delete graph
	void deleteGraph()
	{
		delete graph;
	}
	//functions for the new paths,get teh graph path,node position and node size
	void newPath(int t_start, int t_end);
	std::vector<Node*>& getGraphPath();
	int nodePos(sf::Vector2f position);
	void setNodeSize(int t_size);

private:
	// set the node shaped and colliders and window
	std::vector<sf::RectangleShape> m_nodeShape;
	Collisions m_colliders;
	sf::RenderWindow& m_window;
	//set the node map, graph, end node and start node
	std::map<std::string, int> nodeMap;
	Graph<NodeData, int>* graph;
	int endNode = 2237;
	int startNode = 103;
	//set the raycasr,the transform and graph path and the number of nodes
	Raycast m_raycastUp;
	Transform m_transform;
	std::vector<Node*> graphPath;
	int m_numNodes = 0;
	//set the grid nodes and node data and node index
	std::vector<NodeData> m_gridNodes;
	NodeData nodeData;
	int nodeIndex{ 0 };
	
	// val and row and clos and node sizes
	int val = 0;
	int m_rows = 0;
	int m_cols = 0;
	int m_nodeSize = 0;
};
