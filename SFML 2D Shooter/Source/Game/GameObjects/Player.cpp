#include "Player.h"

#include "CollectibleItem.h"
#include "../Game.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../GameData/GameDataManager.h"
#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/Input/InputDevice.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Engine/Utils/Utils.h"
#include "../Weapons/BlitzWeapon.h"
#include "../../Engine/Renderer/FrameTimer.h"
#include "../Weapons/PistolWeapon.h"

Player::Player():
GameObjectWithAnimatedSprite(m_filename, m_numberOfFrames, m_frameWidth, m_frameHeight, m_isLooped, m_fps, m_color, m_scale, false)
, m_IsMoving(false)
, m_IsSprinting(false)
, m_WeaponOffsetX(0)
, m_WeaponOffsetY(0)
, m_meleeCooldown(2.0f)
, m_meleeCooldownRemaining(0.0f)
, m_isMeleeing(false)
, m_health(5)
, m_maxHealth(5)
, m_score(100)
, m_speed(4.0f)
, m_switchCooldown(2.0f)
, m_switchCooldownRemaining(0.0f)
{
}

Player::~Player()
{
	for (WeaponBase* weapon : m_pWeapons) 
	{
		SAFE_DELETE_PTR(weapon)
	}

	m_pWeapons.clear();
}

void Player::Initialise()
{
	GameDataManager* pGameDataManager = C_SysContext::Get<GameDataManager>();

	SpritesheetDef* pSpritesheetDef;
	pSpritesheetDef = pGameDataManager->GetSpritesheetDef("sprites/characters/spr_biu.xml");

	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(STATE_IDLE, pSpritesheetDef, "spr_biu_idle", 10);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(STATE_WALKING, pSpritesheetDef, "spr_biu_walk", 10);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(STATE_SPRINTING, pSpritesheetDef, "spr_biu_sprint", 10);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(STATE_MELEE, pSpritesheetDef, "spr_biu_melee", 10, false);
	m_AnimatedSprite.SetCurrentAnimation(STATE_IDLE);

	//Set player's initial position
	m_AnimatedSprite.setPosition(800, 400);

	m_WeaponOffsetX = 10;
	m_WeaponOffsetY = 20;

	m_pWeapons.push_back(new BlitzWeapon());
	m_pWeapons.push_back(new PistolWeapon());

	//Initialise each weapon
	for (WeaponBase* weapon : m_pWeapons) {
		weapon->Initialise();
	}

	//Make second weapon invisible until switched to
	m_pWeapons[1]->SetScale(0.0f, 0.0f);

	//Set the current weapon
	m_pCurrentWeapon = m_pWeapons[0];

	//m_pWeapon = new BlitzWeapon();
	//m_pWeapon->Initialise();

	m_CollisionRect = m_AnimatedSprite.getGlobalBounds();
}

void Player::Update()
{
	m_AnimatedSprite.Animate();
	HandlePlayerMovement();
	Melee();
	SwitchWeapon();

	switch (m_AnimatedSprite.GetCurrentAnimation())
	{
		case STATE_IDLE:
		{
			if (m_IsSprinting)
			{
				m_AnimatedSprite.SetCurrentAnimation(STATE_SPRINTING);
			}
			else if (m_IsMoving)
			{
				m_AnimatedSprite.SetCurrentAnimation(STATE_WALKING);
			}
		}
		break;

		case STATE_WALKING:
		{
			if (m_IsSprinting)
			{
				m_AnimatedSprite.SetCurrentAnimation(STATE_SPRINTING);
			}
			else if (!m_IsMoving)
			{
				m_AnimatedSprite.SetCurrentAnimation(STATE_IDLE);
			}
		}
		break;

		case STATE_SPRINTING:
		{
			if (!m_IsSprinting)
			{
				// Transition back to walking or idle based on whether the player is still moving
				m_AnimatedSprite.SetCurrentAnimation(m_IsMoving ? STATE_WALKING : STATE_IDLE);
			}
		}
		break;

		case STATE_MELEE:
		{
			if (m_AnimatedSprite.AnimationFinished())
			{
				m_AnimatedSprite.SetCurrentAnimation(STATE_IDLE);
				m_isMeleeing = false;
			}
		}
		break;

		default:
		{
			
		}
		break;
	}

	const auto pInputManager = C_SysContext::Get<InputManager>();
	const InputDevice* pInputDevice = pInputManager->GetInputDevice();

	//Get the player position and mouse position
	sf::Vector2f playerpos = m_AnimatedSprite.getPosition();
	sf::Vector2f mousepos = pInputDevice->getPointerPos();
	//Convert to world space using player as a reference
	sf::Vector2f worldCentre = playerpos;
	sf::Vector2f screenCentre = sf::Vector2f(pWindowManager->GetWindow()->getSize().x * 0.5f, pWindowManager->GetWindow()->getSize().y * 0.5f);
	int offsetX = worldCentre.x - screenCentre.x;
	int offsetY = worldCentre.y - screenCentre.y;
	mousepos = sf::Vector2f(mousepos.x + offsetX, mousepos.y + offsetY);

	//Calculate the direction vector
	sf::Vector2f direction = mousepos - playerpos;

	//Calculate the angle in radians and then convert it to degrees
	const float PI = 3.1415f;

	float angle = atan2(direction.y, direction.x) * 180 / PI;

	//Determine horizontal orientation, flip the sprite if the mouse is to the left of the player
	bool shouldFlipHorizontally = mousepos.x < playerpos.x;

	//Apply horizontal flip for left or right orientation
	m_pCurrentWeapon->SetScale(shouldFlipHorizontally ? -1.0f : 1.0f, 1.0f);

	//Adjust the angle based on orientation
	if (shouldFlipHorizontally) {
		angle -= 180;
	}

	//Set the rotation of the weapon
	m_pCurrentWeapon->SetRotation(angle);

	//Update the weapon's position
	sf::Vector2f weaponPosition = playerpos;
	weaponPosition.x += m_WeaponOffsetX * m_AnimatedSprite.getScale().x;
	weaponPosition.y += m_WeaponOffsetY * m_AnimatedSprite.getScale().y;
	m_pCurrentWeapon->SetPosition(weaponPosition.x, weaponPosition.y);

	m_pCurrentWeapon->Update();

	if (pInputDevice && pInputDevice->GetAnalogueInput(E_AnalogueInput_LeftTrigger).GetValue() >= 0.1f)
	{
		m_pCurrentWeapon->Fire();
	}

	if (pInputDevice && pInputDevice->GetButtonInput(E_DigitalInput_X).IsDown())
	{
		m_pCurrentWeapon->Reload();
	}

	m_CollisionRect = m_AnimatedSprite.getGlobalBounds();
}

void Player::GetPosition(float& x, float& y)
{
	GameObjectWithAnimatedSprite::GetPosition(x, y);
}

sf::Vector2f Player::GetPosition()
{
	return GameObjectWithAnimatedSprite::GetPosition();
}

void Player::SetPosition(float px, float py)
{
	GameObjectWithAnimatedSprite::SetPosition(px, py);
}

void Player::SetPosition(sf::Vector2f ppos)
{
	GameObjectWithAnimatedSprite::SetPosition(ppos);
}

void Player::HandlePlayerMovement()
{
	const auto pInputManager = C_SysContext::Get<InputManager>();
	const InputDevice* pInputDevice = pInputManager->GetInputDevice();

	//Get the player position and mouse position
	sf::Vector2f playerpos = m_AnimatedSprite.getPosition();

	sf::Vector2f mousepos = pInputDevice->getPointerPos();
	//Convert to world space using player as a reference
	sf::Vector2f worldCentre = playerpos;
	sf::Vector2f screenCentre = sf::Vector2f(pWindowManager->GetWindow()->getSize().x * 0.5f, pWindowManager->GetWindow()->getSize().y * 0.5f);
	int offsetX = worldCentre.x - screenCentre.x;
	int offsetY = worldCentre.y - screenCentre.y;
	mousepos = sf::Vector2f(mousepos.x + offsetX, mousepos.y + offsetY);

	//Checks if the L Shift key or B button is being held down, and if it is then the movement speed
	//is increased by half of it's original value
	if (pInputDevice && pInputDevice->GetButtonInput(E_DigitalInput_B).IsDown())
	{
		m_IsSprinting = true;
		if (m_speed < 6.f)
			m_speed = m_speed * 2;
	}
	//If no longer pressing shift/B button, and is not moving, reduce speed back
	else if (m_IsSprinting == true)
	{
		m_speed = m_speed * 0.5f;
		m_IsSprinting = false;
	}

	//Move left
	if (pInputDevice && pInputDevice->GetButtonInput(E_DigitalInput_DpadLeft).IsDown())
	{
		m_AnimatedSprite.setPosition(m_AnimatedSprite.getPosition().x - m_speed, m_AnimatedSprite.getPosition().y);
		m_IsMoving = true;
	}

	//Move right
	if (pInputDevice && pInputDevice->GetButtonInput(E_DigitalInput_DpadRight).IsDown())
	{
		m_AnimatedSprite.setPosition(m_AnimatedSprite.getPosition().x + m_speed, m_AnimatedSprite.getPosition().y);
		m_IsMoving = true;
	}

	//Move up
	if (pInputDevice && pInputDevice->GetButtonInput(E_DigitalInput_DpadUp).IsDown())
	{
		m_AnimatedSprite.setPosition(m_AnimatedSprite.getPosition().x, m_AnimatedSprite.getPosition().y - m_speed);
		m_IsMoving = true;
	}

	//Move down
	if (pInputDevice && pInputDevice->GetButtonInput(E_DigitalInput_DpadDown).IsDown())
	{
		m_AnimatedSprite.setPosition(m_AnimatedSprite.getPosition().x, m_AnimatedSprite.getPosition().y + m_speed);
		m_IsMoving = true;
	}

	// Check if no movement keys are pressed
	if (!(pInputDevice && (pInputDevice->GetButtonInput(E_DigitalInput_DpadLeft).IsDown() ||
		  pInputDevice->GetButtonInput(E_DigitalInput_DpadRight).IsDown() ||
		  pInputDevice->GetButtonInput(E_DigitalInput_DpadUp).IsDown() ||
		  pInputDevice->GetButtonInput(E_DigitalInput_DpadDown).IsDown())))
	{
		m_IsMoving = false;
	}

	//Turn to face right
	if (mousepos.x > playerpos.x)
	{
		m_AnimatedSprite.setScale(1.0f, 1.0f);
	}
	//Turn to face left
	else if (mousepos.x < playerpos.x)
	{
		m_AnimatedSprite.setScale(-1.0f, 1.0f);
	}
}

void Player::Melee()
{
	//Grab the frame timer
	FrameTimer* pFrameTimer = C_SysContext::Get<FrameTimer>();

	//Decrease the remaining cooldown time
	if (m_meleeCooldownRemaining > 0.0f)
	{
		m_meleeCooldownRemaining -= pFrameTimer->DeltaTime();
	}

	const auto pInputManager = C_SysContext::Get<InputManager>();
	const InputDevice* pInputDevice = pInputManager->GetInputDevice();

	//Checks if melee key has been pressed and enters the melee animation state
	if (pInputDevice && pInputDevice->GetButtonInput(E_DigitalInput_RightShoulder).IsDown())
	{
		if (m_meleeCooldownRemaining <= 0.0f)
		{
			m_AnimatedSprite.SetCurrentAnimation(STATE_MELEE);
			m_isMeleeing = true;
			m_meleeCooldownRemaining = m_meleeCooldown;
		}
	}
}

void Player::SwitchWeapon()
{
	//Grab the frame timer
	FrameTimer* pFrameTimer = C_SysContext::Get<FrameTimer>();

	//Decrease the remaining cooldown time
	if (m_switchCooldownRemaining > 0.0f)
	{
		m_switchCooldownRemaining -= pFrameTimer->DeltaTime();
	}

	const auto pInputManager = C_SysContext::Get<InputManager>();
	const InputDevice* pInputDevice = pInputManager->GetInputDevice();
	const auto pGameStateManager = C_SysContext::Get<GameStateManager>();

	if (m_switchCooldownRemaining <= 0.0f) 
	{
		if (pInputDevice && pInputDevice->GetButtonInput(E_DigitalInput_LeftShoulder).IsDown()) 
		{
			m_pOldWeapon = m_pCurrentWeapon;

			if (m_pCurrentWeapon == m_pWeapons[0]) 
			{
				m_pCurrentWeapon = m_pWeapons[1];
			}
			else 
			{
				m_pCurrentWeapon = m_pWeapons[0];
			}
			m_pOldWeapon->SetScale(0.0f, 0.0f);

			m_switchCooldownRemaining = m_switchCooldown; 
		}
	}
}

void Player::OnCollision(Collider2D* pCollider2D)
{
	if (dynamic_cast<GameObjectWithAnimatedSprite*>(pCollider2D) && m_isMeleeing == true)
	{
		GameObjectWithAnimatedSprite* tenemy = dynamic_cast<GameObjectWithAnimatedSprite*>(pCollider2D);
		GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
		GameState* pCurrentGameState = pGameStateManager->GetCurrentGameState();
		pCurrentGameState->RemoveGameObject(tenemy);
		m_score += 100;
	}
	else if(dynamic_cast<Enemy*>(pCollider2D) && m_isMeleeing == true)
	{
		Enemy* tenemy = dynamic_cast<Enemy*>(pCollider2D);
		GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
		GameState* pCurrentGameState = pGameStateManager->GetCurrentGameState();
		pCurrentGameState->RemoveGameObject(tenemy);
		m_score += 100;
	}
}
