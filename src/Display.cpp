#include "Display.h"

Display::Display() {}

// Return Menu window display
sf::RenderWindow Display::openMenuDisplay()
{
	return sf::RenderWindow(sf::VideoMode((uint16_t)535, (uint16_t)300), "SuperPacman Main Menu");
}

// Return Help window display
sf::RenderWindow Display::openHelpDisplay()
{
	return sf::RenderWindow(sf::VideoMode((uint16_t)WIDTH, (uint16_t)HEIGHT), "SuperPacman Help");
}

// Return Game window display
sf::RenderWindow Display::openGameDisplay(float width, float height)
{
	return sf::RenderWindow(sf::VideoMode((uint16_t)(width * (float)PIXSIZE), (uint16_t)((height+1) * (float)PIXSIZE)),
																			     "SuperPacman Game"); // +1 for UI
}

// Return Lost Game window display
sf::RenderWindow Display::openLostDisplay()
{
	return sf::RenderWindow(sf::VideoMode((uint16_t)515, (uint16_t)300),
											"SuperPacman Lost Game");
}

// Return Win Game window display
sf::RenderWindow Display::openWinDisplay()
{
	return sf::RenderWindow(sf::VideoMode((uint16_t)533, (uint16_t)HEIGHT),
											"SuperPacman Win Game");
}