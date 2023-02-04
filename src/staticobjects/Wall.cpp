#include "Wall.h"
#include "Pacman.h"
#include "Ghost.h"

Wall::Wall(const sf::Texture& texture, sf::Vector2f pos)
	:	StaticObjects(texture, pos) {}

void Wall::draw(sf::RenderWindow& window)
{
	window.draw(getSprite());
}

void Wall::handleCollision(GameObject& obj)
{
    obj.handleCollision(*this);
}

void Wall::handleCollision(Pacman& pacman)
{
	pacman.handleCollision(*this);
}

void Wall::handleCollision(Ghost& ghost)
{
	ghost.handleCollision(*this);
}
