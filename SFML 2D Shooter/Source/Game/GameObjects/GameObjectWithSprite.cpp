#include "GameObjectWithSprite.h"
#include "../Weapons/Bullet.h"
#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/System/Context/SysContextProvider.h"

GameObjectWithSprite::GameObjectWithSprite(const char* spriteFileName, sf::Color spriteColor, sf::Vector2f spriteScale, bool isDestructible)
{
	m_spriteFileName = spriteFileName;
	m_spriteColor = spriteColor;
	m_spriteScale = spriteScale;
	m_isDestructible = isDestructible;
}

void GameObjectWithSprite::SetHUDObject(bool value)
{
	m_isHUD = value;
}

bool GameObjectWithSprite::IsHUDObject() const
{
	return m_isHUD;
}

void GameObjectWithSprite::Initialise()
{
	m_Sprite.Initialise(m_spriteFileName, m_spriteColor, m_spriteScale);
	m_Sprite.setOrigin(m_Sprite.getLocalBounds().width * 0.5f, m_Sprite.getLocalBounds().height * 0.5f);

	m_CollisionRect = m_Sprite.getGlobalBounds();
}

sf::Vector2f GameObjectWithSprite::GetPosition()
{
	return m_Sprite.getPosition();
}

void GameObjectWithSprite::GetPosition(float& x, float& y)
{
	x = m_Sprite.getPosition().x;
	y = m_Sprite.getPosition().y;
}

void GameObjectWithSprite::SetPosition(float px, float py)
{
	sf::Vector2f tpos = sf::Vector2f(px, py);
	m_Sprite.setPosition(tpos);
}

void GameObjectWithSprite::SetPosition(sf::Vector2f ppos)
{
	m_Sprite.setPosition(ppos);
}

void GameObjectWithSprite::Update()
{
	m_CollisionRect = m_Sprite.getGlobalBounds();
}

void GameObjectWithSprite::OnCollision(Collider2D* pCollider2D)
{
	if (m_isDestructible && dynamic_cast<Bullet*>(pCollider2D))
	{
		GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
		GameState* pCurrentGameState = pGameStateManager->GetCurrentGameState();
		pCurrentGameState->RemoveGameObject(this);
	}
}

void GameObjectWithSprite::ChangeSprite(const char* newSpriteFileName)
{
	m_spriteFileName = newSpriteFileName;
	m_Sprite.Initialise(m_spriteFileName, m_spriteColor, m_spriteScale);
}

