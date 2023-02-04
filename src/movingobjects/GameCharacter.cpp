#include "GameCharacter.h"
#include <iostream>

GameCharacter::GameCharacter(const std::vector<sf::Texture>& texture, sf::Vector2f pos)
	:	m_lives(3), MovingObjects(texture, pos) {}

int GameCharacter::getLivesAmount() const
{
	return m_lives;
}

void GameCharacter::lifeDecrease()
{
	m_lives--;
}

void GameCharacter::addLife()
{
	m_lives++;
}
