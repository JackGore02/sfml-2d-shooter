#pragma once
#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Engine/Input/InputDevice.h"
#include "../../Engine/System/GameState/GameStateManager.h"

//Objects
#include "../GameObjects/GameObjectWithSprite.h"
#include "../GameObjects/GameObjectWithSpriteAndText.h"
#include "../GameObjects/GameObjectWithText.h"

class ControlsViewGameState : public GameState
{
public:
	ControlsViewGameState();
	~ControlsViewGameState() override;

	//Public member functions
	void Initialise() override;
	void Update() override;
	GameObject* GetPlayer() override { return nullptr; }

private:
	//Input device
	InputManager* pInputManager = C_SysContext::Get<InputManager>();
	InputDevice* pInputDevice = pInputManager->GetInputDevice();

	//Game State manager
	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();

	//Objects
	//Title
	GameObjectWithSpriteAndText* m_controlsTitle;

	//Controls overview sprite
	GameObjectWithSprite* m_controlsOverview;

	//Return to options button
	GameObjectWithText* m_returnToOptions;
};

