#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>
class Transform
{
public:
	 Transform();
	~ Transform();

	typedef struct Position
	{
		float x = 0;
		float y = 0;
		float z = 0;
	};

	static float distance(sf::Vector2f t_position_1, sf::Vector2f t_position_2);
	static sf::Vector2f moveTowards(sf::Vector2f t_position, sf::Vector2f t_targetPosition, float maxDistance);

	Position position;
private:

};

