#include "Behavior.h"

Behavior::Behavior() {}

void Behavior::setPacmanPos(const sf::Vector2f& pacmanPos)
{
	m_pacmanPos = pacmanPos;
}

void Behavior::setCurrPos(const sf::Vector2f& currPos)
{
	m_currentPos = currPos;
}

sf::Vector2f Behavior::getCurrPos() const
{
	return m_currentPos;
}

sf::Vector2f Behavior::getPacmanPos() const
{
	return m_pacmanPos;
}

sf::Time Behavior::getTime()
{
	return m_time.getElapsedTime();
}

void Behavior::resetClock()
{
	m_time.restart();
}