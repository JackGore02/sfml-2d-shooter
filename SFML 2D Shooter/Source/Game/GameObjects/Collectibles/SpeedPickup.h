#pragma once
#include "../CollectibleItem.h"
#include "../../../Engine/System/GameState/GameStateManager.h"
#include "../../../Engine/System/Context/SysContextProvider.h"
class SpeedPickup :
    public CollectibleItem
{
public:
    SpeedPickup();
   virtual  ~SpeedPickup();

    void OnCollision(Collider2D* pCollider2D) override;
};

