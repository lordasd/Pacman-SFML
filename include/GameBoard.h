#pragma once

#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Ui.h"
#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <SoundManager.h>
#include <SFML/Audio.hpp>

const int MAXLEVEL = 4;

class GameBoard{
public:
	GameBoard(const int level, const int points);
	bool loadLevel();
	void loadObjects();
	// Render all objects on the board
	void draw(sf::RenderWindow& window);
	float getWidth() const;
	float getHeight() const;
	void setCharacterDirection(sf::Keyboard::Key key);
	void moveCharacters(sf::Time delta);
	void handleCollisions();
	int getCookieAmount() const;
	bool isPacmanDead();
	void isKeyDoorStatus();
	bool isPlayerLost() const;
	int getPoints() const;
	void updateUi();
	void addLostTime(float time);
	float getTimeLeft() const;
	void giveGhostPacmanPos();
	void setBonuses();

private:
	float m_rows, m_cols;
	int m_level;
	int m_points;
	int m_cookies = 0;
	float m_levelTime;
	
	std::ifstream m_fin;
	GameObjectFactory m_gameObjFactory;
	std::vector<std::string> m_board;
	Ui m_ui;
	std::vector<std::unique_ptr<GameObject>> m_staticObjects;
	std::vector<std::unique_ptr<GameObject>> m_movingObjects;
	
	void openLevelFile();
	void checkCookieCollision(std::unique_ptr<GameObject>& obj,
							  std::unique_ptr<GameObject>& otherObj);
	void resetGamePositions();
};