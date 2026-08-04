#include "Enemy.h"

#include "../../Engine/System/Context/SysContextProvider.h"
#include "../GameData/GameDataManager.h"

#include "Player.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/Renderer/FrameTimer.h"


Enemy::Enemy()
{
}

void Enemy::Initialise()
{
	GameDataManager* p_GameDataManager = C_SysContext::Get<GameDataManager>();
	SpritesheetDef* p_spritesheet_def1;

	p_spritesheet_def1 = p_GameDataManager->GetSpritesheetDef("sprites/characters/spr_zombieTurtle.xml");

	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_Idle, p_spritesheet_def1, "spr_zombieTurtle_idle", 10);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_Walk, p_spritesheet_def1, "spr_zombieTurtle_walk", 10);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_Death, p_spritesheet_def1, "spr_zombieTurtle_death", 10);

	m_AnimatedSprite.SetCurrentAnimation(E_Idle);
	//m_AnimatedSprite.setPosition(0, 0);

	m_attackCooldownRamaining = m_attackCooldown;
}

void Enemy::Update()
{
	m_AnimatedSprite.Animate();
	m_CollisionRect = m_AnimatedSprite.getGlobalBounds();

	FrameTimer* pFrameTimer = C_SysContext::Get<FrameTimer>();
	if (m_attackCooldownRamaining > 0.0f)
	{
		m_attackCooldownRamaining -= pFrameTimer->DeltaTime();
	}
	

}

sf::Vector2f Enemy::GetPosition()
{
	return m_AnimatedSprite.getPosition();
}

void Enemy::GetPosition(float& x, float & y)
{
	m_AnimatedSprite.getPosition();
}

void Enemy::SetPosition(float px, float py)
{
	m_AnimatedSprite.setPosition(px, py);
}

void Enemy::SetPosition(sf::Vector2f ppos)
{
	m_AnimatedSprite.setPosition(ppos);
}

void Enemy::OnCollision(Collider2D* pCollider2D)
{
	auto* tplayer = dynamic_cast<Player*>(pCollider2D);
	if (tplayer)
	{
		GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
		GameState* pCurrentGameState = pGameStateManager->GetCurrentGameState();

		if (m_attackCooldownRamaining <= 0.0f)
		{
			tplayer->reduceHealth();
			m_attackCooldownRamaining = m_attackCooldown;
		}
	}
	
}

Enemy::~Enemy()
{

}