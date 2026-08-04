#include "AmmoPickup.h"
#include <iostream>
#include "../Player.h"
#include "../../../Engine/System/GameState/GameState.h"
#include "../../Weapons/WeaponBase.h"

AmmoPickup::AmmoPickup()
{
	_type = "Ammo";
	this->_texturepath = "sprites/spr_pickup_light_0.png";

	//std::cout << "Ammo Pickup Created" << std::endl;
}

AmmoPickup::~AmmoPickup()
{
	//std::cout << "Ammo Pickup Destroyed" << std::endl;
}

void AmmoPickup::OnCollision(Collider2D* pCollider2D)
{
	auto* tplayer = dynamic_cast<Player*>(pCollider2D);
		if (tplayer)
		{
			GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
			GameState* pCurrentGameState = pGameStateManager->GetCurrentGameState();

			//Increase player ammo
			tplayer->getWeapon()->increaseAmmo(20);
			//Remove object
			pCurrentGameState->RemoveGameObject(this);
		}
}
