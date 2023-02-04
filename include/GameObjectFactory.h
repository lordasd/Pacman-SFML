#pragma once

#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "SoundManager.h"

class GameObject;

class GameObjectFactory {
public:
	GameObjectFactory(const int points);
	std::unique_ptr<GameObject> createGameObject(char c, sf::Vector2f pos);

private:
	int m_points;
};