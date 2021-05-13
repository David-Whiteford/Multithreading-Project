#pragma once
#include  <string>

// ---------------------------------------------------------------------
//  Name:           NodeData
//  Description:    A simple struct to encapsulate all the node data.
//                  Add or remove fields as required.               
// ---------------------------------------------------------------------
struct NodeData
{
	std::string name;
	int pathCost;
	int CostReachGoalH;
	int row, col;
	int positionX, positionY;
	bool passable;
	sf::Color color;
	int index;
	
};
