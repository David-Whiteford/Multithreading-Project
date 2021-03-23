#pragma once
#include  <string>

// ---------------------------------------------------------------------
//  Name:           NodeData
//  Description:    A simple struct to encapsulate all the node data.
//                  Add or remove fields as required.               
// ---------------------------------------------------------------------
struct NodeData
{
	std::string m_name;
	int pathCost;
	int CostReachGoalH;
	int m_row, m_col;
	int m_x, m_y;
	bool passable;
};
