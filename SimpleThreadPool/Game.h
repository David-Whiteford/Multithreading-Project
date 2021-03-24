#ifndef GAME_H
#define GAME_H
#include "Tilemap.h"
#include <SFML/Graphics.hpp>
#include "MyEnums.h"
#include "Path.h"

#include "NPC.h"
class Game
{
public:
	Game();
	~Game();

	void run();

private:
	void init();
	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();
	void handleInputs();
	Tilemap* m_tileMap;
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::Event event;
	sf::RenderWindow m_window; // main SFML window
	int m_enemyNode = 0;
	std::vector<sf::Vector2f> m_startingPos;
	Path* m_gamePath = new Path(m_window);
	sf::Time m_deltaTime;
	NPC *npc;
};
#endif