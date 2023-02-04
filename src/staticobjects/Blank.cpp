#include "Blank.h"
#include "Pacman.h"

Blank::Blank(const sf::Texture& texture, sf::Vector2f pos)
	: StaticObjects(texture, pos) {}

void Blank::draw(sf::RenderWindow& window)
{
	window.draw(getSprite());
}

void Blank::handleCollision(GameObject& obj)
{
	obj.handleCollision(*this);
}