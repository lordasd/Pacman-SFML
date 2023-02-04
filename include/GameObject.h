#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Direction.h"
#include "TextureManager.h"

enum SpriteStatus {
	NORAML,
	FRIGHTENED
};

class Pacman;
class Wall;
class Ghost;
class Cookie;
class Door;
class Key;
class Bonus;

class GameObject{
public:
	GameObject(const sf::Texture& texture, sf::Vector2f pos);
	GameObject(const std::vector<sf::Texture>& texture, sf::Vector2f pos);
	virtual ~GameObject() = default;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void handleCollision(GameObject& obj) = 0;
	virtual void handleCollision(Pacman& obj) = 0;
	virtual void handleCollision(Ghost& obj) = 0;
	virtual void handleCollision(Wall& obj) = 0;
	virtual void handleCollision(Cookie& obj) = 0;
	virtual void handleCollision(Door& obj) = 0;
	virtual void handleCollision(Key& obj) = 0;
	virtual void handleCollision(Bonus& obj) = 0;
	virtual sf::Sprite& getSprite() = 0;
	sf::Sprite& getMySprite();
	sf::Sprite& getMySprite(int direction);
	sf::Vector2f getPosition() const;
	sf::Vector2f getStartPosition() const;
	void setSpritesPositions(const sf::Vector2f& pos);
	void updateStayTexture(const Direction direction);
	void switchSprites();

protected:
	void setOriginalColor();
	void setSpritesColor(const sf::Color& color);
	SpriteStatus getSpriteStatus() const;

private:
	sf::Vector2f m_position;
	sf::Vector2f m_startPosition;
	std::vector<sf::Sprite> m_sprites;
	std::vector<sf::Sprite> m_scareghost;
	sf::Sprite m_sprite;
	std::vector<sf::Color> m_origColors;
	SpriteStatus m_spriteStatus = NORAML;

	void initSpritesnPositions(std::vector<sf::Sprite>& sprites,
							   const std::vector<sf::Texture>& texture, sf::Vector2f pos);
};