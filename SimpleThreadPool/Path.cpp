#include "Path.h"
#include "Rectangle.h"

Path::Path(sf::RenderWindow& t_window, int t_mapWidth, int t_mapHeigth) :
	m_window(t_window),m_cols(t_mapWidth),m_rows(t_mapHeigth)
{

}

Path::~Path()
{
}

void Path::draw()
{
	if (DEBUG >= 1)
	{
		for (auto node : m_nodeShape)
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
							if (graph->nodeIndex(index)->m_data.row == n_row
								&& graph->nodeIndex(index)->m_data.col == n_col)
							{

								sf::Vector2f currentNode = sf::Vector2f(graph->nodeIndex(nodeIndex)->m_data.positionX,
									graph->nodeIndex(nodeIndex)->m_data.positionY);

								sf::Vector2f neighborsNodes = sf::Vector2f(graph->nodeIndex(index)->m_data.positionX,
									graph->nodeIndex(index)->m_data.positionY);

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
	for (int i = 0; i < graphPath.size(); i++) {
		delete graphPath[i];
	}
	graphPath.clear();
}

void Path::initAStar(std::vector<Rectangles*>& t_walls, Path* t_path)
{
	t_path->m_nodeShape.clear();
	int impassableVal = 1;
	t_path->graph = new Graph<NodeData, int>(t_path->m_numNodes);
	t_path->graphPath.reserve(t_path->m_numNodes);
	int nodeIndex = 0;
	for (int row = 0; row < t_path->m_rows; row++)
	{
		for (int col = 0; col < t_path->m_cols; col++)
		{
			t_path->nodeData.passable = true;
			t_path->nodeData.name = std::to_string(nodeIndex);
			t_path->nodeData.positionX = col * t_path->m_nodeSize;
			t_path->nodeData.positionY = row * t_path->m_nodeSize;
			t_path->nodeData.row = row;
			t_path->nodeData.col = col;
			t_path->nodeData.color = sf::Color::Transparent;
			t_path->nodeData.index = nodeIndex;
			t_path->m_gridNodes.push_back(t_path->nodeData);

			sf::RectangleShape rect;
			t_path->m_nodeShape.push_back(rect);
			t_path->m_nodeShape[nodeIndex].setFillColor(t_path->nodeData.color);
			t_path->m_nodeShape[nodeIndex].setOutlineThickness(0.5f);
			t_path->m_nodeShape[nodeIndex].setOutlineColor(sf::Color::White);
			t_path->m_nodeShape[nodeIndex].setSize(sf::Vector2f(t_path->m_nodeSize, t_path->m_nodeSize));
			t_path->m_nodeShape[nodeIndex].setPosition(t_path->nodeData.positionX, t_path->nodeData.positionY);
			for (auto wall : t_walls)
			{
				if (t_path->m_colliders.boxToBoxCol(t_path->m_nodeShape[nodeIndex].getPosition(),wall->getPosition(),
					t_path->m_nodeShape[nodeIndex].getSize(), wall->getSize()) == true)
				{
					if (wall->myGameObject->getTag() == impassableVal) {
						t_path->m_nodeShape[nodeIndex].setFillColor(sf::Color(sf::Color::Red));
						t_path->nodeData.passable = false;
					}
				}
			}
		
			//add node
			t_path->graph->addNode(t_path->nodeData, nodeIndex);
			nodeIndex++;
		}
		
	}
	t_path->neighbourAlgor();
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

void Path::setNodeSize(int t_size)
{
	m_nodeSize = t_size;
}

