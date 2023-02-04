#include "MenuItem.h"

MenuItem::MenuItem(sf::Sprite sprite)
	:	m_sprite(sprite){}

sf::FloatRect MenuItem::getGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

const sf::Sprite& MenuItem::getSprite() const
{
	return m_sprite;
}

void MenuItem::setPos(float x, float y)
{
	m_sprite.setPosition(x, y);
}