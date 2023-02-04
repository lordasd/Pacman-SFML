#include "StaticObjects.h"

StaticObjects::StaticObjects(const sf::Texture& texture, sf::Vector2f pos)
	:	GameObject(texture, pos) {}

sf::Sprite& StaticObjects::getSprite()
{
	return getMySprite();
}