#pragma once

#include <SFML/Graphics.hpp>

enum class Direction
{
    Up,
    Down,
    Right,
    Left,
    Stay,
    Max,
};

int toInt(const Direction dir);
Direction toDirection(sf::Keyboard::Key key);
sf::Vector2f toVector(Direction dir);