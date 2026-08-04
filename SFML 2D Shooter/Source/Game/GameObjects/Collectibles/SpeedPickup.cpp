#include "SpeedPickup.h"
#include <iostream>
#include "../Player.h"
#include "../../../Engine/System/GameState/GameState.h"

SpeedPickup::SpeedPickup()
{
	_type = "Speed";
	this->_texturepath = "sprites/spr_speed_boost.png";
	//std::cout << "Speed Pickup Created" << std::endl;
}

SpeedPickup::~SpeedPickup()
{
	//std::cout << "Speed Pickup Destroyed" << std::endl;
}

void SpeedPickup::OnCollision(Collider2D* pCollider2D)
{
	auto* tplayer = dynamic_cast<Player*>(pCollider2D);
		if (tplayer)
		{
			GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
			GameState* pCurrentGameState = pGameStateManager->GetCurrentGameState();

			//TODO: Replace with Ammo Addition
			tplayer->increaseSpeed();
			pCurrentGameState->RemoveGameObject(this);
		}
}
