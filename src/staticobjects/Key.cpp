#include "Key.h"
#include "Pacman.h"

Key::Key(const sf::Texture& texture, sf::Vector2f pos, int id)
	:	m_doorOpen(SoundManager::instance().getDoorOpen()),
		m_id(id), StaticObjects(texture, pos) {}

void Key::draw(sf::RenderWindow& window)
{
	if(isAvail())
		window.draw(getSprite());
}

void Key::handleCollision(GameObject& obj)
{
	obj.handleCollision(*this);
}

void Key::handleCollision(Pacman& pacman)
{
	if (m_show)
	{
		m_doorOpen.play();
		m_show = false;
		pacman.handleCollision(*this);
	}
}

bool Key::isAvail() const
{
	return m_show;
}

int Key::getId() const
{
	return m_id;
}

void Key::unshow()
{
	m_show = false;
}
