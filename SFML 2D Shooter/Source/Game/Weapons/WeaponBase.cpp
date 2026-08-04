#include "WeaponBase.h"

#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/Renderer/FrameTimer.h"

WeaponBase::WeaponBase()
:m_Ammo(0)
,m_AmmoInClip(0)
,m_MaxClipSize(0)
,m_FireRate(0)
,m_FireTimer(0)
{
}

WeaponBase::~WeaponBase() = default;

void WeaponBase::Fire()
{
	if (CanFire())
	{
		m_AmmoInClip--;
	}

	if (m_FireRate > 0.0f)
	{
		m_FireTimer = 1.0f / m_FireRate;
	}
}

void WeaponBase::Update()
{
	m_AnimatedSprite.Animate();

	if (m_AnimatedSprite.AnimationFinished())
	{
		m_AnimatedSprite.SetCurrentAnimation(0);
		m_AnimatedSprite.Pause();
	}

	if (m_FireTimer >= 0.0f)
	{
		FrameTimer* pFrameTimer = C_SysContext::Get<FrameTimer>();
		m_FireTimer -= pFrameTimer->DeltaTime();
	}
}

bool WeaponBase::CanFire()
{
	if (m_AmmoInClip > 0 && m_FireTimer <= 0.0f)
	{
		return true;
	}

	return false;
}


void WeaponBase::SetPosition(float posx, float posy)
{
	m_AnimatedSprite.setPosition(posx, posy);
}

void WeaponBase::SetScale(float scaleX, float scaleY)
{
	m_AnimatedSprite.setScale(scaleX, scaleY);
}

void WeaponBase::SetRotation(float angle)
{
	m_AnimatedSprite.setRotation(angle);
}
