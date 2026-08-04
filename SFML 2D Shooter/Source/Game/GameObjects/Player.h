#pragma once

#include "GameObjectWithAnimatedSprite.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/Renderer/WindowManager.h"

class WeaponBase;

class Player : public GameObjectWithAnimatedSprite
{
public:
	Player();
	~Player();

	void Initialise() override;
	void Update() override;
	void GetPosition(float& x, float& y) override;
	sf::Vector2f GetPosition() override;
	void SetPosition(float px, float py) override;
	void SetPosition(sf::Vector2f ppos) override;

	void OnCollision(Collider2D* pCollider2D) override;

	//Get/Setting stats
	//Health
	int getCurrentHealth() { return m_health; }
	int getMaxHealth() { return m_maxHealth; }
	void reduceHealth() { if (m_health > 0) m_health--; }
	void increaseHealth() { if (m_health < m_maxHealth) m_health++; }
	void reduceMaxHealth() { if (m_maxHealth > 1) m_maxHealth--; }
	void increaseMaxHealth() { if (m_maxHealth < 10) m_maxHealth++; }
	void setStats(std::vector<float> stats) { m_health = stats[0]; m_maxHealth = stats[1]; m_score = stats[2]; m_speed = stats[3]; }
	std::vector<float> getStats() { return std::vector<float> {float(m_health), float(m_maxHealth), float(m_score), m_speed}; }
	

	//Score
	int getScore() { return m_score; }
	void increaseScore(int amount) { if (m_score < 99999 - amount) m_score += amount; else m_score = 99999; }
	void decreaseScore(int amount) { if (m_score >= 0 + amount) m_score -= amount; else m_score = 0; }

	//Speed
	float getSpeed() { return m_speed; }
	void increaseSpeed() { m_speed *= 1.2f; }

	//WeaponBase* getWeapon() { return m_pWeapon; }
	WeaponBase* getWeapon() { return m_pCurrentWeapon; }

private:
	enum E_AnimationState
	{
		STATE_IDLE = 0,
		STATE_WALKING = 1,
		STATE_SPRINTING = 2,
		STATE_MELEE = 3
	};

	void HandlePlayerMovement();
	bool m_IsMoving;
	bool m_IsSprinting;

	void Melee();
	float m_meleeCooldown;
	float m_meleeCooldownRemaining;
	bool m_isMeleeing;

	void SwitchWeapon();
	float m_switchCooldown;
	float m_switchCooldownRemaining;

	//Stats
	int m_health;
	int m_maxHealth;
	int m_score;
	float m_speed;

	WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();

protected:
	//WeaponBase* m_pWeapon;
	std::vector<WeaponBase*> m_pWeapons;
	WeaponBase* m_pCurrentWeapon;
	WeaponBase* m_pOldWeapon;
	float m_WeaponOffsetX;
	float m_WeaponOffsetY;
};
