#pragma once
#include "../CollectibleItem.h"
class HealthPickup :
    public CollectibleItem
{
public:
	HealthPickup();
	virtual ~HealthPickup();

	void OnCollision(Collider2D* pCollider2D) override;
};

