#include "Cookie.h"
#include "Pacman.h"

Cookie::Cookie(const sf::Texture& texture, sf::Vector2f pos)
	:	m_show(true), StaticObjects(texture, pos) {}

void Cookie::draw(sf::RenderWindow& window)
{
	if(isAvail())
		window.draw(getSprite());
}

void Cookie::handleCollision(GameObject& obj)
{
	obj.handleCollision(*this);
}

void Cookie::handleCollision(Pacman& pacman)
{
	// If cookie wasn't taken
	if (m_show)
		pacman.handleCollision(*this);
}

bool Cookie::isAvail() const
{
	return m_show;
}

void Cookie::unShow()
{
	m_show = false;
}
