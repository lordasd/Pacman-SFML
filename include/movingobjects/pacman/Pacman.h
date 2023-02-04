#pragma once

#include "GameCharacter.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Direction.h"
#include "PacmanState.h"
#include "BonusState.h"

class Pacman : public GameCharacter{
public:
	Pacman(const std::vector<sf::Texture>& texture, sf::Vector2f pos, const int points);
	void move(sf::Time delta) override;
	void draw(sf::RenderWindow& window) override;
	void handleCollision(GameObject&) override;
	void handleCollision(Pacman&) override {};
	void handleCollision(Ghost&) override;
	void handleCollision(Wall&) override;
	void handleCollision(Cookie&) override;
	void handleCollision(Door&) override;
	void handleCollision(Key&) override;
	void handleCollision(Bonus&) override;
	void die() override;
	PacmanState getState() const;
	BonusState getBonusState() const;
	int getPoints() const;
	void eatCookie();
	void setSuper();
	void unDie();
	void unsetBonus();
	void checkBonusTime();
	float getTimeElapsed() const;

private:
	int m_points;
	bool m_isBonusOn;
	float m_pacmanSpeed = 105.f;
	sf::Sound m_deathSound;
	sf::Sound m_chompSound;
	sf::Sound m_powerPelletSound;
	sf::Sound m_eatGhostSound;
	sf::Sound m_timeExtendSound;
	sf::Sound m_hpSound;
	sf::Sound m_freezeSound;
	sf::Clock m_time;
	PacmanState m_state;
	BonusState m_bonus; // Picked up bonus

	void moveBackwards(GameObject& staticObject);
	bool slideIntoPath(Direction direction, sf::Sprite& sprite, GameObject& staticObject);
	void updateStateColor();
};