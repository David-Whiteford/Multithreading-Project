#ifndef MY_ENUMS
#define MY_ENUMS
#include <random>

/// <summary>
/// different mode game can be 

/// </summary>
enum class GameState
{
	//different game states
	None,
	OverWorld,
	Dungeon,
	Exit

};
namespace
{
	std::random_device rd;
	std::mt19937 mt(rd());
	int randomInt(int t_exclusiveMax)
	{
		std::uniform_int_distribution<> dist(0, t_exclusiveMax - 1);
		return dist(mt);
	}
	int randomInt(int t_min, int t_max)
	{
		std::uniform_int_distribution<> dist(0, t_max - t_min);
		return dist(mt) + t_min;
	}
}
#endif // !MY_ENUMS
