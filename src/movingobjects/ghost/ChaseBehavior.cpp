#include "ChaseBehavior.h"
#include <iostream>

ChaseBehavior::ChaseBehavior(const Direction& direction)
	:	m_currDirection(direction), Behavior() {}

void ChaseBehavior::update()
{
	if (getTime().asSeconds() >= 0.7)
	{
		auto pacmanPos = getPacmanPos();
		auto ghostPos = getCurrPos();

        if (pacmanPos.x == ghostPos.x)
        {
            if (pacmanPos.y > ghostPos.y)
                m_currDirection = Direction::Down;
            else
                m_currDirection = Direction::Up;
        }
        else if (pacmanPos.y == ghostPos.y)
        {
            if (pacmanPos.x > ghostPos.x)
                m_currDirection = Direction::Right;
            else
                m_currDirection = Direction::Left;
        }
        else if (pacmanPos.x > ghostPos.x)
        {
            // Pacman right down
            if (pacmanPos.y >= ghostPos.y)
            {
                if (abs(pacmanPos.x - ghostPos.x) > abs(pacmanPos.y - ghostPos.y))
                    m_currDirection = Direction::Right;
                else
                    m_currDirection = Direction::Down;
            }
            else // Pacman right up
            {
                if (abs(pacmanPos.x - ghostPos.x) > abs(pacmanPos.y - ghostPos.y))
                    m_currDirection = Direction::Right;
                else
                    m_currDirection = Direction::Up;
            }
        }
        else if (pacmanPos.x < ghostPos.x)
        {
            // Pacman left down
            if (pacmanPos.y >= ghostPos.y)
            {
                if (abs(pacmanPos.x - ghostPos.x) > abs(pacmanPos.y - ghostPos.y))
                    m_currDirection = Direction::Left;
                else
                    m_currDirection = Direction::Down;
            }
            else // Pacman left up
            {
                if (abs(pacmanPos.x - ghostPos.x) > abs(pacmanPos.y - ghostPos.y))
                    m_currDirection = Direction::Left;
                else
                    m_currDirection = Direction::Up;
            }        
        }

		resetClock();
	}
}

Direction ChaseBehavior::getDireciton()
{
	return m_currDirection;
}

void ChaseBehavior::setDirection(const Direction& direction)
{
	m_currDirection = direction;
}
