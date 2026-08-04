#include "CollectibleItem.h"

#include "Player.h"
#include "../../Engine/System/GameState/GameState.h"



std::string CollectibleItem::get_Type()
{
	return _type;
}

void CollectibleItem::Update()
{
	m_CollisionRect = m_sprite.getGlobalBounds();
}

sf::Vector2f CollectibleItem::GetPosition()
{
	return m_sprite.getPosition();
}

void CollectibleItem::SetPosition(float px, float py)
{
	m_sprite.setPosition(px, py);
}

void CollectibleItem::SetPosition(sf::Vector2f ppos)
{
	m_sprite.setPosition(ppos);
}

void CollectibleItem::GetPosition(float& x, float& y)
{
	x = m_sprite.getPosition().x;
	y = m_sprite.getPosition().y;
}

void CollectibleItem::Initialise()
{
	m_sprite.Initialise(this->_texturepath.c_str(), sf::Color::White, sf::Vector2f(1.f, 1.f));
	m_CollisionRect = m_sprite.getGlobalBounds();
}



