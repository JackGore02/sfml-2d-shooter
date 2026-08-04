#pragma once
#include "../../Engine/System/GameState/GameState.h"
#include "../GameObjects/GameObjectWithText.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Engine/Input/InputDevice.h"
#include "../../Engine/System/GameState/GameStateManager.h"

#include "../GameObjects/GameObjectWithTileMap.h"

//Game States
#include "../GameStates/OptionsMenuGameState.h"
#include "../GameStates/EndScreenGameState.h"

class GamePlayingGameState : public GameState
{
public:
	//Constructor and Destructor
	GamePlayingGameState();
	~GamePlayingGameState();

	//Public member functions
	void Initialise() override;
	void Update() override;
	GameObject* GetPlayer() override { return nullptr; };

private:
	GameObjectWithText* m_text;

	//Input device
	InputManager* pInputManager = C_SysContext::Get<InputManager>();
	InputDevice* pInputDevice = pInputManager->GetInputDevice();

	//Game State manager
	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
};

