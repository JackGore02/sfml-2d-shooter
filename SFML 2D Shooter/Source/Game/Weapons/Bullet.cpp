#include "Bullet.h"

#include "BlitzWeapon.h"
#include "WeaponBase.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/GameObjectWithSprite.h"
#include "../GameObjects/Enemy.h"

#include "../../Engine/System/Context/SysContextProvider.h"
#include "../GameData/GameDataManager.h"
#include "../../Engine/Renderer/FrameTimer.h"
#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/System/GameState/GameStateManager.h"

Bullet::Bullet()
:m_Velocity(0)
,m_Lifetime(0)
{
}

Bullet::~Bullet() = default;

void Bullet::Initialise()
{
	GameDataManager* pGameDataManager = C_SysContext::Get<GameDataManager>();

	SpritesheetDef* pSpritesheetDef;
	pSpritesheetDef = pGameDataManager->GetSpritesheetDef("sprites/bullets/spr_bullet.xml");

	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(0, pSpritesheetDef, "spr_bullet", 24, false);
	m_AnimatedSprite.SetCurrentAnimation(0);

	m_Velocity = 1500.0f;
	m_Lifetime = 1.0f;

	m_CollisionRect = m_AnimatedSprite.getGlobalBounds();
}

void Bullet::Update()
{
	m_AnimatedSprite.Animate();

	//Don't move until we are passed the muzzle flash
	if (m_AnimatedSprite.GetCurrentFrame() == 0)
		return;

	//Grab the frame timer
	FrameTimer* pFrameTimer = C_SysContext::Get<FrameTimer>();

	//Create a forward vector
	sf::Vector2f movement(1.0f, 0.0f);

	//Modify magnitude based on velocity
	movement *= (m_Velocity * pFrameTimer->DeltaTime());

	//Rotate and scale it to face the correct direction
	sf::Transform transform;
	transform.rotate(m_AnimatedSprite.getRotation());
	transform.scale(m_AnimatedSprite.getScale());
	movement = transform.transformPoint(movement);

	//Transform the bullet position
	m_AnimatedSprite.move(movement);

	m_Lifetime -= pFrameTimer->DeltaTime();
	if (m_Lifetime <= 0.0f)
	{
		GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
		GameState* pGameState = pGameStateManager->GetCurrentGameState();
		//Remove from the current game state
		if (pGameState)
			pGameState->RemoveGameObject(this);
	}

	m_CollisionRect = m_AnimatedSprite.getGlobalBounds();
}

void Bullet::GetPosition(float& x, float& y)
{
	x = m_AnimatedSprite.getPosition().x;
	y = m_AnimatedSprite.getPosition().y;
}

sf::Vector2f Bullet::GetPosition()
{
	return m_AnimatedSprite.getPosition();
}

void Bullet::SetPosition(float px, float py)
{
	sf::Vector2f tpos = sf::Vector2f(px, py);
	m_AnimatedSprite.setPosition(tpos);
}

void Bullet::SetPosition(sf::Vector2f ppos)
{
	m_AnimatedSprite.setPosition(ppos);
}

void Bullet::SetRotation(float angle)
{
	m_AnimatedSprite.setRotation(angle);
}

void Bullet::SetScale(float scaleX, float scaleY)
{
	m_AnimatedSprite.setScale(scaleX, scaleY);
}

void Bullet::OnCollision(Collider2D* pCollider2D)
{
	if (dynamic_cast<GameObjectWithAnimatedSprite*>(pCollider2D))
	{
		if (dynamic_cast<GameObjectWithAnimatedSprite*>(pCollider2D)->m_isDestructible)
		{
			//Remove the hit object and the bullet
			GameObjectWithAnimatedSprite* tsprite = dynamic_cast<GameObjectWithAnimatedSprite*>(pCollider2D);
			GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
			GameState* pCurrentGameState = pGameStateManager->GetCurrentGameState();
			pCurrentGameState->RemoveGameObject(this);
			pCurrentGameState->RemoveGameObject(tsprite);

			//Add score to the player
			Player* tplayer = dynamic_cast<Player*>(pCurrentGameState->GetPlayer());
			tplayer->increaseScore(100);
		}
	}
	else if (dynamic_cast<GameObjectWithSprite*>(pCollider2D))
	{
		if (dynamic_cast<GameObjectWithSprite*>(pCollider2D)->m_isDestructible)
		{
			//Remove the hit object and the bullet
			GameObjectWithSprite* tsprite = dynamic_cast<GameObjectWithSprite*>(pCollider2D);
			GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
			GameState* pCurrentGameState = pGameStateManager->GetCurrentGameState();
			pCurrentGameState->RemoveGameObject(this);
			pCurrentGameState->RemoveGameObject(tsprite);

			//Add score to the player
			Player* tplayer = dynamic_cast<Player*>(pCurrentGameState->GetPlayer());
			tplayer->increaseScore(100);
		}
	}
	else if (dynamic_cast<Enemy*>(pCollider2D))
	{
			//Remove the hit object and the bullet
			Enemy* tsprite = dynamic_cast<Enemy*>(pCollider2D);
			GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
			GameState* pCurrentGameState = pGameStateManager->GetCurrentGameState();
			pCurrentGameState->RemoveGameObject(this);
			pCurrentGameState->RemoveGameObject(tsprite);

			//Add score to the player
			Player* tplayer = dynamic_cast<Player*>(pCurrentGameState->GetPlayer());
			tplayer->increaseScore(100);
		
	}
}
