#pragma once

#include "StaticObjects.h"
#include "TextureManager.h"
#include "SoundManager.h"

class Door : public StaticObjects{
public:
	Door(const sf::Texture& texture, sf::Vector2f pos, int id);
	void draw(sf::RenderWindow& window) override;
	void handleCollision(GameObject&) override;
	void handleCollision(Pacman&) override;
	void handleCollision(Ghost&) override;
	void handleCollision(Wall&) override {};
	void handleCollision(Cookie&) override {};
	void handleCollision(Door&) override {};
	void handleCollision(Key&) override {};
	void handleCollision(Bonus&) override {};
	bool isAvail() const;
	void unshow();
	int getId() const;
private:
	sf::Sound m_doorBreak;
	bool m_show = true;
	int m_id;
};