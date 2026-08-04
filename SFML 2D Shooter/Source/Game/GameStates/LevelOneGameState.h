#pragma once
#include "../../Engine/System/GameState/GameState.h"
#include "../GameObjects/GameObjectWithText.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Engine/Input/InputDevice.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/Renderer/FrameTimer.h"
#include <array>

#include "../GameObjects/GameObjectWithTileMap.h"
#include "../GameObjects/GameObjectWithCamera.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/HUD.h"
#include "../GameObjects/Collectibles/CollectibleFactoryImplementation.h"
#include "../GameObjects/Enemy.h"

//Game States
#include "../GameStates/OptionsMenuGameState.h"
#include "../GameStates/EndScreenGameState.h"

class LevelOneGameState : public GameState
{
public:
	//Constructor and Destructor
	LevelOneGameState();
	~LevelOneGameState();

	//Public member functions
	void Initialise() override;
	void Update() override;
	GameObject* GetPlayer() override { return m_player; }

private:
	GameObjectWithText* m_text;

	//Input device
	InputManager* pInputManager = C_SysContext::Get<InputManager>();
	InputDevice* pInputDevice = pInputManager->GetInputDevice();

	//Game State manager
	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
	//Frame Timer
	FrameTimer* pFrameTimer = C_SysContext::Get<FrameTimer>();

	//Player
	Player* m_player;
	//HUD
	HUD* m_HUD;
	//Game Camera
	GameObjectWithCamera* m_Camera;
};

