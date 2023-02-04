#include "Ghost.h"
#include "Pacman.h"
#include "Wall.h"
#include "Door.h"

#include <iostream>

Ghost::Ghost(const std::vector<sf::Texture>& texture, sf::Vector2f pos)
	:	m_state(GhostState::PATROL),
		GameCharacter(texture, pos) 
{
	m_behavior = createBehavior();
}

void Ghost::draw(sf::RenderWindow& window)
{
	window.draw(getSprite());
}

void Ghost::move(sf::Time delta)
{
	// Update the stay texture to be the last(current) moving texture
	updateStayTexture(getDirection());
	// Update directions of behavior
	m_behavior->update();
	// Update ghost direction
	setDirection(m_behavior->getDireciton());
	// Calculate the movement and move the sprite
	getSprite().move(toVector(getDirection()) * delta.asSeconds() * m_ghostSpeed);
	// Save the new position to be able to get the position at any time
	setSpritesPositions(getSprite().getPosition());
}

void Ghost::handleCollision(GameObject& obj)
{
	obj.handleCollision(*this);
}

void Ghost::handleCollision(Pacman& pacman)
{
	pacman.handleCollision(*this);
}

void Ghost::handleCollision(Wall& wall)
{
	moveBackwards(wall);
}

void Ghost::handleCollision(Door& door)
{
	moveBackwards(door);
}

void Ghost::updatePositions(const sf::Vector2f& pacmanPos)
{
	// Update pacmans pos
	m_behavior->setPacmanPos(pacmanPos);
	// Set also current pos
	m_behavior->setCurrPos(getPosition());
}

GhostState Ghost::getState() const
{
	return m_state;
}

void Ghost::moveBackwards(GameObject& staticObj)
{
	auto direction = getDirection();

	if (direction != Direction::Stay)
	{
		// Tried to slide in a path
		bool slideInto = false;
		auto& sprite = getSprite();
		auto staticSpriteBounds = staticObj.getSprite().getGlobalBounds();

		// Move backwards from wall and update all positions depending on the current direction
		if (direction == Direction::Up)
		{
			while (sprite.getGlobalBounds().intersects(staticSpriteBounds))
			{
				sprite.move(sf::Vector2f(0, 1));
				setSpritesPositions(sprite.getPosition());

				if (slideIntoPath(Direction::Up, sprite, staticObj))
					slideInto = true;
				// Don't accept the same direction
				if(!slideInto)
					while (direction == Direction::Up)
						direction = Direction(rand() % toInt(Direction::Max));
			}
		}
		else if (direction == Direction::Down)
		{
			while (sprite.getGlobalBounds().intersects(staticSpriteBounds))
			{
				sprite.move(sf::Vector2f(0, -1));
				setSpritesPositions(sprite.getPosition());

				if (slideIntoPath(Direction::Down, sprite, staticObj))
					slideInto = true;
				// Don't accept the same direction
				if(!slideInto)
					while (direction == Direction::Down)
						direction = Direction(rand() % toInt(Direction::Max));
			}
		}
		else if (direction == Direction::Right)
		{
			while (sprite.getGlobalBounds().intersects(staticSpriteBounds))
			{
				sprite.move(sf::Vector2f(-1, 0));
				setSpritesPositions(sprite.getPosition());

				if (slideIntoPath(Direction::Right, sprite, staticObj))
					slideInto = true;
				// Don't accept the same direction
				if(!slideInto)
					while (direction == Direction::Right)
						direction = Direction(rand() % toInt(Direction::Max));
			}
		}
		else if (direction == Direction::Left)
		{
			while (sprite.getGlobalBounds().intersects(staticSpriteBounds))
			{
				sprite.move(sf::Vector2f(1, 0));
				setSpritesPositions(sprite.getPosition());

				if (slideIntoPath(Direction::Left, sprite, staticObj))
					slideInto = true;
				// Don't accept the same direction
				if(!slideInto)
					while (direction == Direction::Left)
						direction = Direction(rand() % toInt(Direction::Max));
			}
		}

		// Set final direction
		setDirection(direction);
		// Set new direction
		m_behavior->setDirection(direction);
	}
}

bool Ghost::slideIntoPath(Direction direction, sf::Sprite& sprite, GameObject& staticObject)
{
	// Get global Bounds of the static object
	const auto staticSpriteBounds = staticObject.getSprite().getGlobalBounds();

	// Calculate the distance and fix margin by moving the ghost to the apropriate
	// place so ghost will be able to slide into the path
	// (pos of the wall / 2) -+ result and the same for the ghost. 
	// 20 is the pixel margin I give so he will slide in.

	// Direction of ghost
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
	}// Direction of ghost
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


std::unique_ptr<Behavior> Ghost::createBehavior()
{
	if (m_state == GhostState::CHASE) {
		return std::make_unique<ChaseBehavior>(getDirection());
	}
	else if (m_state == GhostState::FRIGHTENED) {
		return std::make_unique<FrightenedBehavior>(getDirection());
	}
	else if (m_state == GhostState::PATROL) {
		return std::make_unique<PatrolBehavior>(getDirection());
	}
	else
		return nullptr;
}

void Ghost::updateGhostState(const Pacman& pacman)
{
	// Claculate distance from pacman
	auto pacDistX = abs(m_behavior->getPacmanPos().x - getPosition().x);
	auto pacDistY = abs(m_behavior->getPacmanPos().y - getPosition().y);
	auto dist = hypot(pacDistX, pacDistY);

	// Choose Ghost state
	switch (m_state)
	{
	case GhostState::PATROL:
		m_ghostSpeed = 90.f;
		// Pacman is close, start chasing
		if (dist < 200)
		{
			m_state = GhostState::CHASE;
			m_behavior = createBehavior();
		}
		else if (pacman.getState() == PacmanState::Super)
		{	// Pacman is super, run away
			m_state = GhostState::FRIGHTENED;
			m_behavior = createBehavior();
			// Switch sprites to Frightened
			if (getSpriteStatus() == NORAML)
				switchSprites();
		}
		break;
	case GhostState::CHASE:
		m_ghostSpeed = 90.f;
		if (dist >= 200)
		{ // Pacman ran away, start patroling
			m_lastState = m_state;
			m_state = GhostState::PATROL;
			m_behavior = createBehavior();
		}
		else if (pacman.getState() == PacmanState::Super)
		{
			// Pacman is super, run away
			m_lastState = m_state;
			m_state = GhostState::FRIGHTENED;
			m_behavior = createBehavior();
			// Switch sprites to Frightened
			if (getSpriteStatus() == NORAML)
				switchSprites();
		}
		break;
	case GhostState::FRIGHTENED:
		// Last 1.5 seconds of flickering
		if (pacman.getTimeElapsed() > 8.5f)
			switchSprites();

		// Slow down
		m_ghostSpeed = 70.f;
		// When pacman is in Super mode
		if (pacman.getState() != PacmanState::Super)
		{
			if (dist < 200)
			{
				m_lastState = m_state;
				m_state = GhostState::CHASE;
				m_behavior = createBehavior();
				// Switch sprites to normal
				if (getSpriteStatus() == FRIGHTENED)
					switchSprites();
			}
			else
			{
				m_lastState = m_state;
				m_state = GhostState::PATROL;
				m_behavior = createBehavior();
				// Switch sprites to normal
				if (getSpriteStatus() == FRIGHTENED)
					switchSprites();
			}
		}
		break;
	case GhostState::DEAD:
		// Last 1.5 seconds of flickering
		if (m_lastState == GhostState::FRIGHTENED)
			if (pacman.getTimeElapsed() > 8.5f)
				switchSprites();

		if (m_time.getElapsedTime().asSeconds() >= 4)
		{
			m_lastState = m_state;
			m_state = GhostState::PATROL;
			m_behavior = createBehavior();
			// Switch sprites to normal
			if (getSpriteStatus() == FRIGHTENED)
				switchSprites();
		}
		break;
	case GhostState::FROZEN:
		// Last 1.5 seconds of flickering
		if (m_lastState == GhostState::FRIGHTENED)
			if (pacman.getTimeElapsed() > 8.5f)
				switchSprites();

		if (m_time.getElapsedTime().asSeconds() >= 5)
		{
			m_state = m_lastState;
			if (m_lastState == GhostState::FRIGHTENED && getSpriteStatus() == NORAML)
				switchSprites();
			m_behavior = createBehavior();
		}
		break;
	default:
		m_state = GhostState::PATROL;
		m_behavior = createBehavior();
	}
}

void Ghost::die()
{
	// Can't kill again if already dead
	if (m_state != GhostState::DEAD)
	{
		m_state = GhostState::DEAD;
		m_ghostSpeed = 0.f;
		// Start a timer for death
		m_time.restart();
	}
}

void Ghost::freeze()
{
	// Save last state to get back after being frozen
	m_lastState = m_state;
	// Set Frozen state
	m_state = GhostState::FROZEN;
	// Freeze ghost by setting the speed to 0
	m_ghostSpeed = 0.f;
	// Restart counter for being frozen
	m_time.restart();
}