#include "PatrolBehavior.h"

PatrolBehavior::PatrolBehavior(const Direction& direction)
	:	m_currDirection(direction), Behavior() {}

void PatrolBehavior::update()
{
	if (getTime().asSeconds() >= 3 + rand() % (6 - 3 + 1))
	{
		// Get new direction randomly
		m_currDirection = Direction(rand() % toInt(Direction::Max));
		// Reset timer for ghost since last change of direction
		resetClock();
	}
}

Direction PatrolBehavior::getDireciton()
{
	return m_currDirection;
}

void PatrolBehavior::setDirection(const Direction& direction)
{
	m_currDirection = direction;
}
