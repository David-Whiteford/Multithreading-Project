#include "Transform.h"

Transform::Transform()
{
}

Transform::~Transform()
{
}

float Transform::distance(sf::Vector2f t_position_1, sf::Vector2f t_position_2)
{
	//get the distance of two vectors
	float x = t_position_2.x - t_position_1.x;
	float y = t_position_2.y - t_position_1.y;
	return std::sqrt(((x * x) + (y * y)));
}
sf::Vector2f Transform::moveTowards(sf::Vector2f t_position, sf::Vector2f t_targetPosition, float t_maxDistance)
{
	//set teh vectors to move to
	float toVecX = t_targetPosition.x - t_position.x;
	float toVecY = t_targetPosition.y - t_position.y;
	//get the square rout of distance
	float squaredDistance = toVecX * toVecX + toVecY * toVecY;
	if (squaredDistance == 0 || t_maxDistance >= 0
		&& squaredDistance <= t_maxDistance * t_maxDistance)
	{
		return t_targetPosition;

	}
	//get the distance
	float distance = std::sqrt(squaredDistance);
	sf::Vector2f position;
	//get teh position and return
	position.x = t_position.x + toVecX / distance * t_maxDistance;
	position.y = t_position.y + toVecY / distance * t_maxDistance;
	return position;
}
