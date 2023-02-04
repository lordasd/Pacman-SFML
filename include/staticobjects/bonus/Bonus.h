#pragma once

#include "StaticObjects.h"
#include "BonusType.h"

class Bonus : public StaticObjects{
public:
	Bonus(const sf::Texture& texture, sf::Vector2f pos, const BonusType& type);
	void handleCollision(GameObject&) override;
	void handleCollision(Pacman&) override;
	void handleCollision(Ghost&) override {};
	void handleCollision(Wall&) override {};
	void handleCollision(Cookie&) override {};
	void handleCollision(Door&) override {};
	void handleCollision(Key&) override {};
	void handleCollision(Bonus&) override {};
	void draw(sf::RenderWindow& window) override;
	BonusType getType() const;
protected:
	void unshow();

private:
	bool m_show = true;
	BonusType m_type;
};