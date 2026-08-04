#include "CollectibleFactoryImplementation.h"

CollectibleItem* CollectibleFactoryImplementation::MakeCollectible(int id)
{
// This function returns the actual Item relating to our Enum
// if this is not an enum value, then it will return null

	CollectibleItem* titem = nullptr;

	switch (id)
	{
	case Type_Ammo:
	{
		titem = new AmmoPickup();
	}
	break;
	case Type_Health:
	{
		titem = new HealthPickup();
	}
	break;
	case Type_Speed:
	{
		titem = new SpeedPickup();
	}
	break;
	default:
		break;
	}

	return titem;
}
