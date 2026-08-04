#pragma once
#include "../CollectibleItem.h"

class CollectibleFactory
{
public:
	virtual CollectibleItem* MakeCollectible(int id) = 0;
};

