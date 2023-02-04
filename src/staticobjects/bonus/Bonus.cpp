#include "Bonus.h"
#include "Pacman.h"

Bonus::Bonus(const sf::Texture& texture, sf::Vector2f pos, const BonusType& type)
	:	m_type(type), StaticObjects(texture, pos) {}

void Bonus::handleCollision(GameObject& obj)
{
	obj.handleCollision(*this);
}

void Bonus::handleCollision(Pacman& pacman)
{
	if (m_show)
	{
		m_show = false;
		pacman.handleCollision(*this);
	}
}

void Bonus::draw(sf::RenderWindow& window)
{
	if (m_show)
		window.draw(getSprite());
}

BonusType Bonus::getType() const
{
	return m_type;
}

void Bonus::unshow()
{
	m_show = false;
}
