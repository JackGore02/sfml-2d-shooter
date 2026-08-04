#pragma once

#include "WeaponBase.h"

class BlitzWeapon : public WeaponBase
{
public:
	BlitzWeapon();
	~BlitzWeapon() override;

	void Initialise() override;
	void Reload() override;
	void Update() override;
	void Fire() override;
	const char* getSpriteFile() override;

protected:
	int m_BarrelOffsetX;
	int m_BarrelOffsetY;
};
