#pragma once

#include "StaticObjects.h"
#include "TextureManager.h"
#include "SoundManager.h"

class Key : public StaticObjects{
public:
	Key(const sf::Texture& texture, sf::Vector2f pos, int id);
	void draw(sf::RenderWindow& window) override;
	void handleCollision(GameObject& obj) override;
	void handleCollision(Pacman& pacman) override;
	void handleCollision(Ghost&) override {};
	void handleCollision(Wall&) override {};
	void handleCollision(Cookie&) override {};
	void handleCollision(Door&) override {};
	void handleCollision(Key&) override {};
	void handleCollision(Bonus&) override {};
	bool isAvail() const;
	int getId() const;
	void unshow();
private:
	sf::Sound m_doorOpen;
	bool m_show = true;
	int m_id;
};