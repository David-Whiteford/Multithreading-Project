#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>

const int PASSIBLE_TAG = 0, IMPASSIBLE_TAG = 1 , ENEMY_TAG=2;

class GameObject
{
public:
	GameObject() { static int _id; id = _id++; }

	virtual ~GameObject() {}
	void setTag(int tag) { m_tag = tag; }
	int getTag() { return m_tag; }

	sf::Vector2f position;
	float size;

	int id;


private:
	int m_tag;
};