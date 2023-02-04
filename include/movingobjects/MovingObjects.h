#pragma once

#include "GameObject.h"
#include "Direction.h"

class MovingObjects : public GameObject{
public:
	MovingObjects(const std::vector<sf::Texture>& texture, sf::Vector2f pos);
	virtual ~MovingObjects() = default;
	virtual void move(sf::Time delta) = 0;
	void setDirection(const Direction& direction);
	void setDirection(sf::Keyboard::Key key);
	Direction getDirection() const;
	sf::Sprite& getSprite() override;
private:
	Direction m_direction;
};