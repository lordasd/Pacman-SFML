#include "Direction.h"
#include <stdexcept>

int toInt(const Direction dir)
{
    switch (dir)
    {
    case Direction::Up:
        return 0;
    case Direction::Down:
        return 1;
    case Direction::Right:
        return 2;
    case Direction::Left:
        return 3;
    case Direction::Stay:
        return 4;
    case Direction::Max:
        return 5;
    default:
        throw std::runtime_error("Unknown direction");
    }
}

Direction toDirection(sf::Keyboard::Key key)
{
    switch (key)
    {
    case sf::Keyboard::Left:
        return Direction::Left;
    case sf::Keyboard::Right:
        return Direction::Right;
    case sf::Keyboard::Up:
        return Direction::Up;
    case sf::Keyboard::Down:
        return Direction::Down;
    case sf::Keyboard::Space:
        return Direction::Stay;
    default:
        throw std::runtime_error("Unknown key");
    }
}

sf::Vector2f toVector(Direction dir)
{
    switch (dir)
    {
        case Direction::Up:
            return { 0, -1 };
        case Direction::Down:
            return { 0, 1 };
        case Direction::Right:
            return { 1, 0 };
        case Direction::Left:
            return { -1, 0 };
        case Direction::Stay:
            return { 0, 0 };
        default:
            throw std::runtime_error("Unknown direction");
    }
}