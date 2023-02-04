#include "GameObjectFactory.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Blank.h"
#include "Wall.h"
#include "Door.h"
#include "Cookie.h"
#include "Key.h"
#include "Bonus.h"

GameObjectFactory::GameObjectFactory(const int points)
    :   m_points(points) {}

std::unique_ptr<GameObject> GameObjectFactory::createGameObject(char c, sf::Vector2f pos)
{
    static int m_doorNum = 1;
    static int m_keyNum = 1;

    switch (c) {
    case ' ':
        return std::make_unique<Blank>(TextureManager::instance().getBlank(), pos);
    case 'a':
        return std::make_unique<Pacman>(TextureManager::instance().getPacman(), pos, m_points);
    case '1':
        // Set the correct location on map corresponding to 50px
        pos.x += 10.f;
        pos.y += 4.f;
        return std::make_unique<Ghost>(TextureManager::instance().getBlinky(), pos);
    case '2':
        // Set the correct location on map corresponding to 50px
        pos.x += 10.f;
        pos.y += 4.f;
        return std::make_unique<Ghost>(TextureManager::instance().getPinky(), pos);
    case '3':
        // Set the correct location on map corresponding to 50px
        pos.x += 10.f;
        pos.y += 4.f;
        return std::make_unique<Ghost>(TextureManager::instance().getInky(), pos);
    case '4':
        // Set the correct location on map corresponding to 50px
        pos.x += 10.f;
        pos.y += 4.f;
        return std::make_unique<Ghost>(TextureManager::instance().getClyde(), pos);
    case '#':
        return std::make_unique<Wall>(TextureManager::instance().getWall(), pos);
    case '*':
    {
        // Set the correct location on map corresponding to 50px
        pos.x += 20.f;
        pos.y += 20.f;
        return std::make_unique<Cookie>(TextureManager::instance().getCookie(), pos);
    }
    case '%':
        pos.x += 10.f;
        pos.y += 10.f;
        return std::make_unique<Key>(TextureManager::instance().getKey(), pos, m_keyNum++);
    case 'D':
        return std::make_unique<Door>(TextureManager::instance().getDoor(), pos, m_doorNum++);
    case '$':
        pos.x += 10.f;
        pos.y += 10.f;
        return std::make_unique<Bonus>(TextureManager::instance().getSuperBonus(), pos, BonusType::Super);
    case '!':
        pos.x += 10.f;
        pos.y += 10.f;
        return std::make_unique<Bonus>(TextureManager::instance().getTimeFreezeBonus(), pos, BonusType::TimeFreeze);
    case '^':
        pos.x += 10.f;
        pos.y += 10.f;
        return std::make_unique<Bonus>(TextureManager::instance().getLifeBonus(), pos, BonusType::Life);
    case '~':
        pos.x += 10.f;
        pos.y += 10.f;
        return std::make_unique<Bonus>(TextureManager::instance().getTimeBonus(), pos, BonusType::Time);
    default:
        return nullptr;
    }
}
