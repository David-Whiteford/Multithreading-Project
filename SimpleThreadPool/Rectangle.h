#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>



class Rectangles : public GameObject
{
public:
	Rectangles(sf::RenderWindow& t_window, float size, sf::Vector2f pos) :
		m_window(t_window)
	{
		m_rect.setPosition(pos);
		m_rect.setFillColor(sf::Color::Green);
		m_rect.setSize(sf::Vector2f(size, size));
		m_rect.setOrigin(sf::Vector2f(size / 2, size / 2));
		myGameObject = dynamic_cast<GameObject*>(this);
		myGameObject->setTag(WALL_TAG);

	} // end wall
	virtual ~Rectangles() {}
	sf::RectangleShape getShape() { return m_rect; }
	void setPosition(sf::Vector2f(t_pos)) { m_rect.setPosition(t_pos); }
	void setShape(sf::RectangleShape shapeParam) { m_rect = shapeParam; }
	void draw() { m_window.draw(m_rect); }
	GameObject* myGameObject;

private:

	sf::RenderWindow& m_window;
	sf::RectangleShape m_rect;
};
