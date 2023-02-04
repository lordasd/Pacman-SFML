#pragma once

#include "SFML/Graphics.hpp"

class MenuItem{
public:
	MenuItem(sf::Sprite sprite);
	sf::FloatRect getGlobalBounds() const;
	const sf::Sprite& getSprite() const;
	void setPos(float x, float y);
private:
	sf::Sprite m_sprite;
};