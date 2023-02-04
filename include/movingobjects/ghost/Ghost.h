#pragma once

#include "GameCharacter.h"
#include "GhostState.h"
#include "Behavior.h"
#include "ChaseBehavior.h"
#include "FrightenedBehavior.h"
#include "PatrolBehavior.h"
#include "Direction.h"
#include <memory>
#include <vector>

class Ghost : public GameCharacter {
public:
	Ghost(const std::vector<sf::Texture>& texture, sf::Vector2f pos);
	void die() override;
	void draw(sf::RenderWindow& window) override;
	void move(sf::Time delta) override;
	void handleCollision(GameObject&) override;
	void handleCollision(Pacman&) override;
	void handleCollision(Ghost&) override {};
	void handleCollision(Wall&) override;
	void handleCollision(Cookie&) override {};
	void handleCollision(Door&) override;
	void handleCollision(Key&) override {};
	void handleCollision(Bonus&) override {};
	void updatePositions(const sf::Vector2f& pacmanPos);
	void updateGhostState(const Pacman& pacman);
	void freeze();
	GhostState getState() const;
private:
	float m_ghostSpeed = 90.f;
	sf::Clock m_time;
	GhostState m_state;
	GhostState m_lastState = GhostState::PATROL;
	std::unique_ptr<Behavior> m_behavior;

	std::unique_ptr<Behavior> createBehavior();
	void moveBackwards(GameObject& staticObj);
	bool slideIntoPath(Direction direction, sf::Sprite& sprite, GameObject& staticObject);
};