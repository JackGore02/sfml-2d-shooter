#pragma once

#include "../../Engine/Renderer/AnimatedSprite.h"

class WeaponBase
{
public:
	WeaponBase();
	virtual ~WeaponBase();

	//Pure virtual functions
	virtual void Initialise() = 0;
	virtual void Reload() = 0;

	//Other virtual functions
	virtual void Update() = 0;
	virtual void Fire() = 0;

	bool CanFire();
	void SetPosition(float posx, float posy);
	void SetScale(float scaleX, float scaleY);
	void SetRotation(float angle);
	virtual const char* getSpriteFile() = 0;

	int GetTotalAmmo() { return m_Ammo; }
	int GetClipAmmo() { return m_AmmoInClip; }
	void increaseAmmo(int amount) { m_Ammo += amount; }

protected:
	int m_Ammo;
	int m_AmmoInClip;
	int m_MaxClipSize;
	float m_FireRate;
	float m_FireTimer;
	AnimatedSprite m_AnimatedSprite;
};
