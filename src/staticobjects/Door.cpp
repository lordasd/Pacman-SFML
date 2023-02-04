#include "Door.h"
#include "Pacman.h"
#include "Ghost.h"

Door::Door(const sf::Texture& texture, sf::Vector2f pos, int id)
	:	m_doorBreak(SoundManager::instance().getDoorBreak()),
		m_id(id), StaticObjects(texture, pos) {}

void Door::draw(sf::RenderWindow& window)
{
	if(m_show)
		window.draw(getSprite());
}

void Door::handleCollision(GameObject& obj)
{
	obj.handleCollision(*this);
}

void Door::handleCollision(Pacman& pacman)
{
	if (m_show)
	{
		if (pacman.getState() == PacmanState::Super)
		{
			m_doorBreak.play();
			m_show = false;
		}
		else
			pacman.handleCollision(*this);
	}
}

void Door::handleCollision(Ghost& ghost)
{
	if(m_show)
		ghost.handleCollision(*this);
}

bool Door::isAvail() const
{
	return m_show;
}

void Door::unshow()
{
	m_show = false;
}

int Door::getId() const
{
	return m_id;
}
