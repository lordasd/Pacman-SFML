#pragma once

#include <sfml/Graphics.hpp>
#include "TextureManager.h"
#include <vector>
#include <string>

class Ui {
public:
	Ui() = default;
	Ui(float height, int level, int points, float levelTime);
	void draw(sf::RenderWindow& window) const;
	void setHp(const int hp);
	void setLevel(const int hp);
	void setPoints(const int);
	void updateTime();
	void saveTime(float time);
	float getTimeLeft() const;
	void addTime();
private:
	std::vector<sf::Sprite> m_hpSprites;
	sf::Sprite m_level;
	sf::Text m_levelNm;
	sf::Sprite m_points;
	sf::Text m_pointsNm;
	sf::Sprite m_timer;
	sf::Text m_timerNm;
	sf::Clock m_clock;
	float m_levelTime;
	float m_saveTime = 0.f; // Sum of all waiting times
	int m_hpNm = 3;
};