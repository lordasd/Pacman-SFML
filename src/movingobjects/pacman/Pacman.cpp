#include "Pacman.h"
#include "Wall.h"
#include "Cookie.h"
#include "Ghost.h"
#include "Key.h"
#include "Door.h"
#include <Bonus.h>

Pacman::Pacman(const std::vector<sf::Texture>& texture, sf::Vector2f pos, const int points)
	:	m_points(points), m_isBonusOn(false), m_bonus(BonusState::None),
		m_chompSound(SoundManager::instance().getChomp()),
		m_deathSound(SoundManager::instance().getPacmanDeath()),
		m_powerPelletSound(SoundManager::instance().getPowerPellet()),
		m_eatGhostSound(SoundManager::instance().getGhostDeath()),
		m_timeExtendSound(SoundManager::instance().getExtendTime()),
		m_hpSound(SoundManager::instance().getHp()),
		m_freezeSound(SoundManager::instance().getFreeze()),
		m_state(PacmanState::Normal), GameCharacter(texture, pos) {}

void Pacman::move(sf::Time delta)
{
	// Calculate the movement and move the sprite
	getSprite().move(toVector(getDirection()) * delta.asSeconds() * m_pacmanSpeed);
	// Save current position
	setSpritesPositions(getSprite().getPosition());
}

void Pacman::draw(sf::RenderWindow& window)
{
	// Update color if Super or normal state
	updateStateColor();
	// Draw the sprite in window
	window.draw(getSprite());
}

void Pacman::die()
{
	// enter if not dead already
	if (m_state == PacmanState::Normal)
	{   // die
		m_state = PacmanState::Dead;
		lifeDecrease();
		setDirection(Direction::Stay);
		// Play pacman death sound
		m_deathSound.play();
		// Pause until music finishes
		while (m_deathSound.getStatus() == sf::Sound::Playing);
	}
}

void Pacman::eatCookie()
{
	m_points += 10;
}

int Pacman::getPoints() const
{
	return m_points;
}

void Pacman::setSuper()
{
	m_state = PacmanState::Super;
	m_powerPelletSound.setLoop(true);
	m_powerPelletSound.play();
	// Set timer for Super mode
	m_time.restart();
}

PacmanState Pacman::getState() const
{
	return m_state;
}

void Pacman::unDie()
{
	// Revive pacman
	m_state = PacmanState::Normal;
}


void Pacman::handleCollision(GameObject& obj)
{
	obj.handleCollision(*this);
}

void Pacman::handleCollision(Ghost& ghost)
{
	if (m_state != PacmanState::Super)
		die();
	else
	{
		if (ghost.getState() != GhostState::DEAD)
		{
			// Ghost is frozen(dead)
			ghost.die();
			// Get 20 points for killing a ghost;
			m_points += 20;
			m_eatGhostSound.play();
		}
	}
}

void Pacman::handleCollision(Wall& wall)
{
	// Block movement towards a wall
	moveBackwards(wall);
}

void Pacman::handleCollision(Cookie& cookie)
{
	if (getSprite().getGlobalBounds().intersects(cookie.getSprite().getGlobalBounds()))
	{
		if (cookie.isAvail())
		{
			// Make cookie not being drawn
			cookie.unShow();
			// Get points for eating cookie
			eatCookie();
			// Play cookie eating sound
			m_chompSound.play();
		}
	}
}

void Pacman::handleCollision(Door& door)
{
	// Block movement towards a wall
	moveBackwards(door);
}

void Pacman::handleCollision(Key& obj)
{
	obj.handleCollision(*this);
}

void Pacman::handleCollision(Bonus& bonus)
{
	if (bonus.getType() == BonusType::Super)
	{
		m_bonus = BonusState::Super;
		m_points += 50;
	}
	else if (bonus.getType() == BonusType::Life)
	{
		m_bonus = BonusState::Life;
		m_hpSound.play();
	}
	else if (bonus.getType() == BonusType::Time)
	{
		m_bonus = BonusState::Time;
		m_timeExtendSound.play();
	}
	else if (bonus.getType() == BonusType::TimeFreeze)
	{
		m_bonus = BonusState::TimeFreeze;
		m_freezeSound.play();
	}
}

void Pacman::moveBackwards(GameObject& staticObject)
{
	// Tried to slide in a path
	bool slideInto = false;

	Direction direction = getDirection();

	if (direction != Direction::Stay)
	{
		auto& sprite = getSprite();
		const auto staticSpriteBounds = staticObject.getSprite().getGlobalBounds();

		if (direction == Direction::Up)
		{
			// Move backwards from wall
			while (sprite.getGlobalBounds().intersects(staticSpriteBounds))
				sprite.move(sf::Vector2f(0, 1));

			if (slideIntoPath(Direction::Up, sprite, staticObject))
				slideInto = true;
		}
		else if (direction == Direction::Down)
		{
			// Move backwards from wall
			while (sprite.getGlobalBounds().intersects(staticSpriteBounds))
				sprite.move(sf::Vector2f(0, -1));

			if (slideIntoPath(Direction::Down, sprite, staticObject))
				slideInto = true;
		}
		else if (direction == Direction::Right)
		{
			// Move backwards from wall
			while (sprite.getGlobalBounds().intersects(staticSpriteBounds))
				sprite.move(sf::Vector2f(-1, 0));

			if (slideIntoPath(Direction::Right, sprite, staticObject))
				slideInto = true;
		}
		else if (direction == Direction::Left)
		{
			// Move backwards from wall
			while (sprite.getGlobalBounds().intersects(staticSpriteBounds))
				sprite.move(sf::Vector2f(1, 0));

			if(slideIntoPath(Direction::Left, sprite, staticObject))
				slideInto = true;
		}

		// Move all other textures backwards
		setSpritesPositions(sprite.getPosition());

		// Stop pacman if collides with a wall and not tries to slide into a path
		if(!slideInto)
			setDirection(Direction::Stay);
	}
}

bool Pacman::slideIntoPath(Direction direction, sf::Sprite& sprite, GameObject& staticObject)
{
	// Get global Bounds of the static object
	const auto staticSpriteBounds = staticObject.getSprite().getGlobalBounds();

	// Calculate the distance and fix margin by moving the pacman to the apropriate
	// place so pacman will be able to slide into the path
	// (pos of the wall / 2) -+ result and the same for the pacman. 
	// 20 is the pixel margin I give so he will slide in.

	// Direction of pacman
	if (direction == Direction::Up || direction == Direction::Down)
	{
		if (abs((sprite.getPosition().x - sprite.getGlobalBounds().width / 2.f) -
			(staticObject.getPosition().x + staticSpriteBounds.width / 2.f)) < 20)
		{	// Move right
			sprite.move(sf::Vector2f(1, 0));
			return true;
		}
		else if (abs((sprite.getPosition().x + sprite.getGlobalBounds().width / 2.f) -
			(staticObject.getPosition().x - staticSpriteBounds.width / 2.f)) < 20)
		{	// Move left
			sprite.move(sf::Vector2f(-1, 0));
			return true;
		}
	}// Direction of pacman
	else if (direction == Direction::Left || direction == Direction::Right)
	{
		if (abs((sprite.getPosition().y - sprite.getGlobalBounds().height / 2.f) -
			(staticObject.getPosition().y + staticSpriteBounds.height / 2.f)) < 20)
		{	// Move down
			sprite.move(sf::Vector2f(0, 1));
			return true;
		}
		else if (abs((sprite.getPosition().y + sprite.getGlobalBounds().height / 2.f) -
			(staticObject.getPosition().y - staticSpriteBounds.height / 2.f)) < 20)
		{	// Move up
			sprite.move(sf::Vector2f(0, -1));
			return true;
		}
	}

	return false;
}

void Pacman::updateStateColor()
{
	if (m_state == PacmanState::Normal)
		setOriginalColor();
	else if (m_state == PacmanState::Super)
		setSpritesColor(sf::Color::Red);
}

BonusState Pacman::getBonusState() const
{
	return m_bonus;
}

void Pacman::unsetBonus()
{
	m_bonus = BonusState::None;
}

void Pacman::checkBonusTime()
{
	// Turn off super
	if (m_time.getElapsedTime().asSeconds() >= 10)
	{
		m_state = PacmanState::Normal;
		m_powerPelletSound.stop();
	}
}

float Pacman::getTimeElapsed() const
{
	return m_time.getElapsedTime().asSeconds();
}
