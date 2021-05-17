#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>
class Transform
{
public:
	 Transform();
	~ Transform();
	//set up the struct of the position
	typedef struct Position
	{
		float x = 0;
		float y = 0;
		float z = 0;
	};
	//set up the distance and move towards function
	static float distance(sf::Vector2f t_position_1, sf::Vector2f t_position_2);
	static sf::Vector2f moveTowards(sf::Vector2f t_position, sf::Vector2f t_targetPosition, float maxDistance);
	//sets up the position
	Position position;
private:

};

