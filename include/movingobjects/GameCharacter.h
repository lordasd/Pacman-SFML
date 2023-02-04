#pragma once

#include "MovingObjects.h"

class GameCharacter : public MovingObjects{
public:
	GameCharacter(const std::vector<sf::Texture>& texture, sf::Vector2f pos);
	virtual ~GameCharacter() = default;
	virtual void die() = 0;
	int getLivesAmount() const;
	void addLife();

protected:
	void lifeDecrease();
private:
	int m_lives;
};