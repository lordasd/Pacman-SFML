#pragma once

#include "TextureManager.h"
#include "SoundManager.h"
#include "Display.h"
#include "GameState.h"
#include "GameBoard.h"
#include "MainMenu.h"
#include "Time.h"
#include <SFML/Graphics.hpp>
#include <Windows.h>

class Controller{
public:
	Controller();
	void run();
private:
	void runMainMenu();
	void runGame(const int levels);
	void runHelp();
	void lostGame();
	void winGame();
	void getReady(sf::RenderWindow& runWindow, GameBoard& m_board);
	void setMouseCursor(sf::RenderWindow& window);
	void nextLevel(const GameBoard& board);
	bool isGameLost(const GameBoard& board);
	int levelCount();

	Display m_display;
	MainMenu m_mainMenu;
	sf::Clock m_time;
	GameState m_state;
	sf::Sound m_startMusic;
	sf::Sound m_siren1;
	sf::Sound m_intermission;
	sf::Sound m_win;
	sf::Sound m_lose;
	sf::Cursor m_cursor;
	int m_level = 1;
	int m_points = 0;
};