#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "MyEnums.h"

class Game
{
public:
	Game();
	~Game();

	void run();

private:
	void init();
	void processEvents();
	void update(double dt);
	void render();
	void handleInputs();

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::Event event;
	sf::RenderWindow m_window; // main SFML window




};
#endif