#pragma once

#include <SFML/Graphics.hpp>
#include "Direction.h"
#include <cmath>

class Behavior {
public:
	Behavior();
	virtual ~Behavior() = default;
	virtual void update() = 0;
	virtual Direction getDireciton() = 0;
	virtual void setDirection(const Direction& direction) = 0;
	void setPacmanPos(const sf::Vector2f& pacmanPos);
	void setCurrPos(const sf::Vector2f& currPos);
	sf::Vector2f getPacmanPos() const;
protected:
	sf::Vector2f getCurrPos() const;
	sf::Time getTime();
	void resetClock();
private:
	sf::Vector2f m_currentPos;
	sf::Vector2f m_pacmanPos;
	sf::Clock m_time;
};