#include "FrightenedBehavior.h"
#include <iostream>

FrightenedBehavior::FrightenedBehavior(const Direction& direction)
	:	m_currDirection(direction), Behavior() {}

void FrightenedBehavior::update()
{
    if (getTime().asSeconds() >= 1)
    {
        auto pacmanPos = getPacmanPos();
        auto ghostPos = getCurrPos();

        if (pacmanPos.x == ghostPos.x)
        {
            if (pacmanPos.y > ghostPos.y)
                m_currDirection = Direction::Up;
            else
                m_currDirection = Direction::Down;
        }
        else if (pacmanPos.y == ghostPos.y)
        {
            if (pacmanPos.x > ghostPos.x)
                m_currDirection = Direction::Left;
            else
                m_currDirection = Direction::Right;
        }
        else if (pacmanPos.x > ghostPos.x)
        {
            // Pacman right down
            if (pacmanPos.y >= ghostPos.y)
            {
                if (abs(pacmanPos.x - ghostPos.x) > abs(pacmanPos.y - ghostPos.y))
                    m_currDirection = Direction::Left;
                else
                    m_currDirection = Direction::Up;
            }
            else // Pacman right up
            {
                if (abs(pacmanPos.x - ghostPos.x) > abs(pacmanPos.y - ghostPos.y))
                    m_currDirection = Direction::Left;
                else
                    m_currDirection = Direction::Down;
            }
        }
        else if (pacmanPos.x < ghostPos.x)
        {
            if (pacmanPos.y >= ghostPos.y)
            {
                if (abs(pacmanPos.x - ghostPos.x) > abs(pacmanPos.y - ghostPos.y))
                    m_currDirection = Direction::Right;
                else
                    m_currDirection = Direction::Up;
            }
            else 
            {
                if (abs(pacmanPos.x - ghostPos.x) > abs(pacmanPos.y - ghostPos.y))
                    m_currDirection = Direction::Right;
                else
                    m_currDirection = Direction::Down;
            }
        }

        resetClock();
    }
}

Direction FrightenedBehavior::getDireciton()
{
	return m_currDirection;
}

void FrightenedBehavior::setDirection(const Direction& direction)
{
	m_currDirection = direction;
}
