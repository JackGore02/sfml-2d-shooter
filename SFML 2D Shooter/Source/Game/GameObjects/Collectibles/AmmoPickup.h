#pragma once
#include "../CollectibleItem.h"
#include "../../../Engine/System/GameState/GameStateManager.h"
#include "../../../Engine/System/Context/SysContextProvider.h"
class AmmoPickup :
    public CollectibleItem
{
	public:
	AmmoPickup();
	virtual ~AmmoPickup();

	void OnCollision(Collider2D* pCollider2D) override;
};

