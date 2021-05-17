#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>



class Rectangles : public GameObject
{
public:
	Rectangles(sf::RenderWindow& t_window, float size, sf::Vector2f pos,int t_tag,sf::Color t_color) :
		m_window(t_window)
	{
		//set up the positiona nd the color
		m_rect.setPosition(pos);
		m_rect.setFillColor(t_color);
		m_rect.setSize(sf::Vector2f(size, size));
		myGameObject = dynamic_cast<GameObject*>(this);
		//checks the tag and set the collision tag
		if (t_tag == 0)
		{
			myGameObject->setTag(PASSIBLE_TAG);
		}
		else if (t_tag == 1)
		{
			myGameObject->setTag(IMPASSIBLE_TAG);
		}
		else if(t_tag == 3)
		{
			myGameObject->setTag(PLAYER_TAG);
		}

	} // end wall
	virtual ~Rectangles() {}
	//get the rectangeles and posiion
	sf::RectangleShape getShape() { return m_rect; }
	sf::Vector2f getPosition() { 
		sf::Vector2f pos = m_rect.getPosition(); 
		return pos;
	}
	//get teh size
	sf::Vector2f getSize() { 
		sf::Vector2f size = m_rect.getSize(); 
		return size;
	}
	//set the position and the shape and draw functions
	void setPosition(sf::Vector2f(t_pos)) { m_rect.setPosition(t_pos); }
	void setShape(sf::RectangleShape shapeParam) { m_rect = shapeParam; }
	void draw() { m_window.draw(m_rect); }
	GameObject* myGameObject;

private:

	sf::RenderWindow& m_window;
	sf::RectangleShape m_rect;
};
