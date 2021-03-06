#include "NPC.h"

NPC::NPC(sf::RenderWindow& t_window, sf::Time& t_deltaTime, sf::Vector2f t_position, Path* t_gamePath, int t_size, sf::RectangleShape t_player)
	:   m_window(t_window), m_deltaTime(t_deltaTime),
		m_position(t_position), m_gamePath(t_gamePath),m_size(t_size),m_player(t_player)
{
	enemyInit();
}

NPC::~NPC()
{
	delete(m_gamePath);
	delete(this);
}

void NPC::enemyInit()
{
	graphPath.reserve(169);
	myGameObject = dynamic_cast<GameObject*>(this);
	m_enemy.setSize(sf::Vector2f(m_size, m_size));
	m_enemy.setFillColor(sf::Color::Green);
	m_enemy.setPosition(m_position);
	setSpeed(1);
	dynamic_cast<GameObject*>(this)->setTag(ENEMY_TAG);
}

void NPC::setSpeed(float t_speed)
{
	m_speed = t_speed;
}

void NPC::setPosition(sf::Vector2f t_pos)
{
	m_enemy.setPosition(t_pos);
}

void NPC::update()
{
	//sets the node the player and the enemy are in
	m_playerNode = m_gamePath->nodePos(m_player.getPosition());
	m_enemyNode = m_gamePath->nodePos(m_enemy.getPosition());
	myGameObject->position = m_enemy.getPosition();
	enemyMovement(m_deltaTime);
}

void NPC::enemyMovement(sf::Time t_deltaTime)
{
	//if path not empty then move
	if (graphPath.empty() == false)
	{
		moveEnemy(t_deltaTime);
	}
	else
	{
		//this sets the end node for now
		int nodeEnd = getPlayerNode(m_endPos);
		m_gamePath->newPath(m_enemyNode, nodeEnd);
		m_gamePath->update();
		graphPath = m_gamePath->getGraphPath();	
		m_gamePath->setColor(sf::Color::Blue, graphPath);
	}
}

void NPC::moveEnemy(sf::Time t_deltaTime)
{
	graphPathVec = sf::Vector2f(graphPath.back()->m_data.positionX, graphPath.back()->m_data.positionY);
	//graphPath[0]->m_data.pathCost = 100;
	sf::Vector2f moveTo = m_transform.moveTowards(m_enemy.getPosition(), graphPathVec, m_speed );
	m_enemy.setPosition(moveTo);
	//once a ai gets to the nodes then delete that node
	if (m_enemy.getPosition().x == graphPath.back()->m_data.positionX &&
		m_enemy.getPosition().y == graphPath.back()->m_data.positionY)
	{
		graphPath.pop_back();
	}
}

void NPC::draw()
{
	//draw ai
	m_window.draw(m_enemy);
}
