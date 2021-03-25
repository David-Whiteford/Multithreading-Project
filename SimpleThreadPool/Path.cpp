#include "Path.h"
#include "Rectangle.h"

Path::Path(sf::RenderWindow& t_window) :
	m_window(t_window)
{

}

Path::~Path()
{
}

void Path::draw()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		for (auto node : m_nodeSquare)
		{
			m_window.draw(node);
		}
	}
}



void Path::neighbourAlgor()
{
	int nodeIndex = 0;
	for (int row = 0; row < m_rows; row++)
	{
		for (int col = 0; col < m_cols; col++)
		{
			// L neighbors Algorithm:
			for (int direction = 0; direction < 9; direction++)
			{
				if (direction == 4) continue; // Skip 4, this is ourself.

				int n_row = row + ((direction % 3) - 1); // Neighbor row
				int n_col = col + ((direction / 3) - 1); // Neighbor column

				// Check the bounds:
				if (n_row >= 0 && n_row < m_rows && n_col >= 0 && n_col < m_cols)
				{
					int index = 0;
					for (int i = 0; i < m_rows; i++)
					{
						for (int j = 0; j < m_cols; j++)
						{
							if (graph->nodeIndex(index)->m_data.m_row == n_row
								&& graph->nodeIndex(index)->m_data.m_col == n_col)
							{

								sf::Vector2f currentNode = sf::Vector2f(graph->nodeIndex(nodeIndex)->m_data.m_x,
									graph->nodeIndex(nodeIndex)->m_data.m_y);

								sf::Vector2f neighborsNodes = sf::Vector2f(graph->nodeIndex(index)->m_data.m_x,
									graph->nodeIndex(index)->m_data.m_y);

								float dist = m_transform.distance(currentNode, neighborsNodes);

								//std::cout << "distance" << dist << std::endl;
								// When moving on the diagonal, cost is sqrt(50*50+50*50)
								graph->addArc(nodeIndex, index, dist);

							}
							index++;
						}
					}

				}
			}
			nodeIndex++;
		}
	}
}

void Path::clearAStar()
{
	graphPath.clear();
}

void Path::initAStar(std::vector<Rectangles*>& t_walls)
{
	int impassableVal = 1;
	graph = new Graph<NodeData, int>(m_numNodes);
	graphPath.reserve(169);
	int nodeIndex = 0;

	int x = 0;
	int y = 0;
	for (int row = 0; row < m_rows; row++)
	{
		for (int col = 0; col < m_cols; col++)
		{
			m_nodeSquare.push_back(m_nodeShape[nodeIndex]);
			nodeData.passable = true;
			nodeData.m_name = std::to_string(nodeIndex);
			nodeData.m_x = col * m_nodeSize;
			nodeData.m_y = row * m_nodeSize;
			nodeData.m_row = row;
			nodeData.m_col = col;

			m_nodeShape[nodeIndex].setFillColor(sf::Color::Transparent);
			m_nodeShape[nodeIndex].setSize(sf::Vector2f(m_nodeSize, m_nodeSize));
			m_nodeShape[nodeIndex].setOutlineThickness(1);
			m_nodeShape[nodeIndex].setOutlineColor(sf::Color(sf::Color::White));
			m_nodeShape[nodeIndex].setPosition(nodeData.m_x, nodeData.m_y);


			for (auto wall : t_walls)
			{
				if (m_nodeShape[nodeIndex].getGlobalBounds().intersects(wall->getShape().getGlobalBounds()))
				{
					if (wall->myGameObject->getTag() == impassableVal)
					{
						m_nodeShape[nodeIndex].setFillColor(sf::Color(sf::Color::Red));
						nodeData.passable = false;
					}

				}
			}

			//std::cout << "The Node at: " << nodeData.m_name << "Is Passable: " << nodeData.passable << std::endl;

			//add node
			graph->addNode(nodeData, nodeIndex);
			m_nodeSquare.push_back(m_nodeShape[nodeIndex]);
			nodeIndex++;
			x++;
		}
		
	}
	neighbourAlgor();
}

void Path::update()
{
	setPath();
}

void Path::setPath()
{
	graph->clearMarks();
	graph->aStar(graph->nodeIndex(startNode), graph->nodeIndex(endNode), graphPath);

}
void Path::newPath(int t_start, int t_end)
{
	startNode = t_start;
	endNode = t_end;
}
std::vector<Node*>& Path::getGraphPath()
{
	return graphPath;
}
int Path::nodePos(sf::Vector2f position)
{
	int nodeNumber = floor(position.x / m_nodeSize) + (floor(position.y / m_nodeSize) * m_cols);
	return nodeNumber;
}
