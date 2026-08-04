#pragma once
#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/Input/InputDevice.h"

//Game Objects
#include "../GameObjects/GameObjectWithSpriteAndText.h"
#include "../GameObjects/GameObjectWithSprite.h"
#include "../GameObjects/GameObjectWithText.h"

//Game States
#include "OptionsMenuGameState.h"
#include "LevelOneGameState.h"

class MainMenuGameState : public GameState
{
public:
	//Constructor and Destructor
	MainMenuGameState();
	~MainMenuGameState() override;

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

	//Title
	GameObjectWithText* m_gameTitle;

	//Menu items
	GameObjectWithSpriteAndText* m_startButton;
	GameObjectWithSpriteAndText* m_optionsButton;
	GameObjectWithSpriteAndText* m_exitButton;

	std::vector<GameObjectWithSpriteAndText*> m_menuItems;
	int m_highlightIndex;
};

