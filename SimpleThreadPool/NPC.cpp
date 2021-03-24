#include "NPC.h"

NPC::NPC(sf::RenderWindow& t_window, sf::Time& t_deltaTime, sf::Vector2f t_position, Path* t_gamePath)
	:   m_window(t_window), m_deltaTime(t_deltaTime),
		m_position(t_position), m_gamePath(t_gamePath)
{
	m_endNodes.push_back(52);
	enemyInit();
}

NPC::~NPC()
{
	delete(m_gamePath);
	delete(this);
}

void NPC::enemyInit()
{
	m_gamePath->clearAStar();
	graphPath.reserve(169);
	myGameObject = dynamic_cast<GameObject*>(this);

	m_enemy.setSize(sf::Vector2f(m_size, m_size));
	m_enemy.setFillColor(sf::Color::Red);
	m_enemy.setPosition(100, 800);
	//get initial enemy Position
	m_enemyNode = m_gamePath->nodePos(m_enemy.getPosition());
	//will take a player position when created
	m_playerNode = getPlayerNode(sf::Vector2f(200, 300));
	m_gamePath->newPath(m_enemyNode, m_playerNode);
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

void NPC::update(sf::RectangleShape t_player, sf::Time t_deltaTime)
{
	//sets the node the player and the enemy are in
	m_playerNode = m_gamePath->nodePos(t_player.getPosition());
	m_enemyNode = m_gamePath->nodePos(m_enemy.getPosition());
	myGameObject->position = m_enemy.getPosition();

	if (m_doOncePatrol != 1)
	{
		m_doOncePatrol = 1;
		graphPath.resize(0);
	}
	enemyMovement(t_deltaTime);
}

void NPC::enemyMovement(sf::Time t_deltaTime)
{
	if (graphPath.empty() == false)
	{
		moveEnemy(t_deltaTime);
	}
	else
	{
		int nodeEnd = getPlayerNode(sf::Vector2f(200, 50));
		m_gamePath->newPath(m_enemyNode, nodeEnd);
		m_gamePath->update();
		graphPath = m_gamePath->getGraphPath();
	}
}

void NPC::moveEnemy(sf::Time t_deltaTime)
{
	graphPathVec = sf::Vector2f(graphPath.back()->m_data.m_x, graphPath.back()->m_data.m_y);

	sf::Vector2f moveTo = m_transform.moveTowards(m_enemy.getPosition(), graphPathVec, m_speed * t_deltaTime.asMilliseconds());
	m_enemy.setPosition(moveTo);
	if (m_enemy.getPosition().x == graphPath.back()->m_data.m_x &&
		m_enemy.getPosition().y == graphPath.back()->m_data.m_y)
	{
		graphPath.pop_back();
	}
}

void NPC::draw()
{
	m_window.draw(m_enemy);
}
