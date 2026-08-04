#pragma once
#include "CollectibleFactory.h"
#include  "AmmoPickup.h"
#include  "HealthPickup.h"
#include  "SpeedPickup.h"

class CollectibleFactoryImplementation :
    public CollectibleFactory
{
public:
    enum PickupType
    {
	    Type_Ammo,
        Type_Health,
        Type_Speed
    };

    virtual CollectibleItem* MakeCollectible(int id) override;
};

