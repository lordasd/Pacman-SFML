#include "GameObject.h"

GameObject::GameObject(const sf::Texture& texture, sf::Vector2f pos)
	:	m_sprite(texture), m_position(pos), m_startPosition(pos)
{
	m_sprite.setPosition(pos);
}

GameObject::GameObject(const std::vector<sf::Texture>& texture, sf::Vector2f pos)
	:	m_position(pos), m_startPosition(pos)
{
	// Set original sprites and their positions
	initSpritesnPositions(m_sprites, texture, pos);
	// Set scared ghost sprites and their positions
	initSpritesnPositions(m_scareghost, TextureManager::instance().getScaredGhost(), pos);

	// Get original colors to return all sprites once changed
	for(int i = 0; i < toInt(Direction::Max); ++i)
		m_origColors.emplace_back(m_sprites[i].getColor());
}

sf::Sprite& GameObject::getMySprite()
{
	return m_sprite;
}

sf::Sprite& GameObject::getMySprite(int direction)
{
	return m_sprites[direction];
}

sf::Vector2f GameObject::getPosition() const
{
	return m_position;
}

sf::Vector2f GameObject::getStartPosition() const
{
	return m_startPosition;
}

void GameObject::setSpritesPositions(const sf::Vector2f& pos)
{
	// Set all sprites(directions) positions to be the same
	for (int i = 0; i < toInt(Direction::Max); i++)
	{
		m_sprites[i].setPosition(pos);
		m_scareghost[i].setPosition(pos);
	}
	m_position = pos;
}

void GameObject::updateStayTexture(const Direction direction)
{
	m_sprites[toInt(Direction::Stay)] = m_sprites[toInt(direction)];
	m_scareghost[toInt(Direction::Stay)] = m_scareghost[toInt(direction)];
}

void GameObject::switchSprites()
{
	// Switch sprites when ghosts are scared or not
	std::vector<sf::Sprite> tempSprites = m_sprites;
	m_sprites = m_scareghost;
	m_scareghost = tempSprites;

	// Set status of m_sprites member of ghosts(What sprites is it holding)
	if (m_spriteStatus == NORAML)
		m_spriteStatus = FRIGHTENED;
	else
		m_spriteStatus = NORAML;
}

void GameObject::setSpritesColor(const sf::Color& color)
{
	for (int i = 0; i < toInt(Direction::Max); ++i)
		m_sprites[i].setColor(color);
}

SpriteStatus GameObject::getSpriteStatus() const
{
	return m_spriteStatus;
}

void GameObject::setOriginalColor()
{
	for (int i = 0; i < toInt(Direction::Max); ++i)
		m_sprites[i].setColor(m_origColors[i]);
}

void GameObject::initSpritesnPositions(std::vector<sf::Sprite>& sprites,
									   const std::vector<sf::Texture>& texture, sf::Vector2f pos)
{
	sprites.emplace_back(sf::Sprite(texture[toInt(Direction::Up)]));
	sprites.back().setPosition(pos);
	sprites.emplace_back(sf::Sprite(texture[toInt(Direction::Down)]));
	sprites.back().setPosition(pos);
	sprites.emplace_back(sf::Sprite(texture[toInt(Direction::Right)]));
	sprites.back().setPosition(pos);
	sprites.emplace_back(sf::Sprite(texture[toInt(Direction::Left)]));
	sprites.back().setPosition(pos);
	sprites.emplace_back(sf::Sprite(texture[toInt(Direction::Left)]));
	sprites.back().setPosition(pos);
}