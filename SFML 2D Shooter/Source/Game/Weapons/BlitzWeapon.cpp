#include "BlitzWeapon.h"

#include "Bullet.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../GameData/GameDataManager.h"

BlitzWeapon::BlitzWeapon()
:m_BarrelOffsetX(0)
,m_BarrelOffsetY(0)
{
	
}

BlitzWeapon::~BlitzWeapon() = default;

void BlitzWeapon::Initialise()
{
	m_Ammo = 30;
	m_AmmoInClip = 6;
	m_MaxClipSize = 6;
	m_FireRate = 0;
	m_FireTimer = 0;

	auto* pGameDataManager = C_SysContext::Get<GameDataManager>();
	SpritesheetDef* pSpritesheetDef = pGameDataManager->GetSpritesheetDef("sprites/weapons/spr_blitz.xml");

	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(0, pSpritesheetDef, "spr_blitz", 24, false);
	m_AnimatedSprite.SetCurrentAnimation(0);
	m_AnimatedSprite.Pause();

	m_BarrelOffsetX = 0;
	m_BarrelOffsetY = 0;
}

void BlitzWeapon::Reload()
{
	int ammoNeeded = m_MaxClipSize - m_AmmoInClip;
	int ammoToReload = std::min(ammoNeeded, m_Ammo);

	m_Ammo -= ammoToReload;
	m_AmmoInClip += ammoToReload;
}

void BlitzWeapon::Update()
{
	WeaponBase::Update();
}

void BlitzWeapon::Fire()
{
	if (!CanFire())
		return;

	WeaponBase::Fire();

	//Generate bullet
	Bullet* bullet = new Bullet();

	bullet->Initialise();

	//Create a bullet spawn offset
	sf::Vector2f bulletSpawnOffset(sf::Vector2i(m_BarrelOffsetX, m_BarrelOffsetY));

	//Rotate it to face the correct direction
	sf::Transform transform;
	transform.rotate(m_AnimatedSprite.getRotation());
	transform.scale(m_AnimatedSprite.getScale());
	bulletSpawnOffset = transform.transformPoint(bulletSpawnOffset);

	bullet->SetPosition(m_AnimatedSprite.getPosition().x + bulletSpawnOffset.x, m_AnimatedSprite.getPosition().y + bulletSpawnOffset.y);
	bullet->SetRotation(m_AnimatedSprite.getRotation());
	bullet->SetScale(m_AnimatedSprite.getScale().x, m_AnimatedSprite.getScale().y);

	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
	GameState* pGameState = pGameStateManager->GetCurrentGameState();

	//Add it to the current game state
	if (pGameState)
		pGameState->AddGameObject(bullet);

	m_AnimatedSprite.Play();
}

const char* BlitzWeapon::getSpriteFile()
{
	return "sprites/HUD/blitzweapon.png";
}
