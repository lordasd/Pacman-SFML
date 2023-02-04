#pragma once

#include "GameObject.h"

class StaticObjects : public GameObject{
public:
	StaticObjects(const sf::Texture& texture, sf::Vector2f pos);
	sf::Sprite& getSprite() override;
};