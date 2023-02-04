#include "MovingObjects.h"

MovingObjects::MovingObjects(const std::vector<sf::Texture>& texture, sf::Vector2f pos)
	:	m_direction(Direction::Stay), GameObject(texture, pos) {}


void MovingObjects::setDirection(const Direction& direction)
{
	m_direction = direction;
}

void MovingObjects::setDirection(sf::Keyboard::Key key)
{
	// Change direction of pacman
	m_direction = toDirection(key);
}

Direction MovingObjects::getDirection() const
{
	return m_direction;
}

sf::Sprite& MovingObjects::getSprite()
{
	// Return specific sprite of the current direction
	return getMySprite(toInt(m_direction));
}