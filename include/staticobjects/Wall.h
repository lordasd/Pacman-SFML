#pragma once

#include "StaticObjects.h"
#include "TextureManager.h"

class Wall : public StaticObjects{
public:
	Wall(const sf::Texture& texture, sf::Vector2f pos);
	void draw(sf::RenderWindow& window) override;
	void handleCollision(GameObject&) override;
	void handleCollision(Pacman&) override;
	void handleCollision(Ghost&) override;
	void handleCollision(Wall&) override {};
	void handleCollision(Cookie&) override {};
	void handleCollision(Door&) override {};
	void handleCollision(Key&) override {};
	void handleCollision(Bonus&) override {};
};