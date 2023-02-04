#pragma once

#include "MenuItem.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "GameState.h"
#include <vector>

const int ITEMS = 3;

class MainMenu{
public:
	MainMenu();
	void handleMouseInput(sf::Vector2f mPosition, GameState& state);
	void handleMouseLocation(sf::Vector2f mPosition);
	void drawMenu(sf::RenderWindow& window);
	void drawHelp(sf::RenderWindow& window);
	void drawLost(sf::RenderWindow& window);
	void drawWin(sf::RenderWindow& window, const int points);

private:
	sf::Sprite m_menuSprite;
	sf::Sprite m_helpSprite;
	sf::Sprite m_winSprite;
	sf::Sprite m_lostSprite;
	std::vector<MenuItem> m_menuItems;
	std::vector<MenuItem> m_menuItemsHighlighted;

	bool m_playh, m_helph, m_exith;
	sf::Sound m_select;

	void setOutsidePos();
};