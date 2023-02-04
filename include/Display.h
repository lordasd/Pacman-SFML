#pragma once

#include <SFML/Graphics.hpp>

// Default values
enum Default {
	WIDTH = 600,
	HEIGHT = 800,
	PIXSIZE = 50
};

class Display {
public:
	Display();
	sf::RenderWindow openMenuDisplay();
	sf::RenderWindow openHelpDisplay();
	sf::RenderWindow openGameDisplay(float width, float height);
	sf::RenderWindow openLostDisplay();
	sf::RenderWindow openWinDisplay();
};