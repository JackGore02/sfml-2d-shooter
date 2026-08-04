#include "HealthPickup.h"
#include "../../../Engine/System/GameState/GameStateManager.h"
#include "../../../Engine/System/Context/SysContextProvider.h"
#include <iostream>
#include "../Player.h"
#include "../../../Engine/System/GameState/GameState.h"

HealthPickup::HealthPickup()
{
	_type = "Health";
	a = 10;
	b = 0;
	c = 0;
	this->_texturepath = "sprites/spr_pickup_health_0.png";
}

HealthPickup::~HealthPickup()
{
	//std::cout << "Health Pickup Destroyed" << std::endl;
}

void HealthPickup::OnCollision(Collider2D* pCollider2D)
{
	auto* tplayer = dynamic_cast<Player*>(pCollider2D);
		if (tplayer)
		{
			GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
			GameState* pCurrentGameState = pGameStateManager->GetCurrentGameState();

			//TODO: Replace with Ammo Addition
			tplayer->increaseHealth();
			pCurrentGameState->RemoveGameObject(this);
		}

}
