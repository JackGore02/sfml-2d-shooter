#pragma once
#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Engine/Input/InputDevice.h"
#include "../../Engine/System/GameState/GameStateManager.h"

//Objects
#include "../GameObjects/GameObjectWithText.h"
#include "../GameObjects/GameObjectWithSpriteAndText.h"

//Game States
#include "ControlsViewGameState.h"

class OptionsMenuGameState : public GameState
{
public:
	//Constructor and Destructor
	OptionsMenuGameState();
	~OptionsMenuGameState() override;

	//Public member functions
	void Initialise() override;
	void Update() override;
	GameObject* GetPlayer() override { return nullptr; }
	bool wasGamePlaying = false;

private:
	//Input device
	InputManager* pInputManager = C_SysContext::Get<InputManager>();
	InputDevice* pInputDevice = pInputManager->GetInputDevice();

	//Game State manager
	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();

	//Title
	GameObjectWithSpriteAndText* m_optionsTitle;

	//Menu Items
	GameObjectWithSpriteAndText* m_controlsButton;
	GameObjectWithSpriteAndText* m_returnToMenuButton;
	GameObjectWithSpriteAndText* m_returnToGameButton;

	std::vector<GameObjectWithSpriteAndText*> m_menuItems;
	int m_highlightIndex;

};

